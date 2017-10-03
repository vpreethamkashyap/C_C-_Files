#include <inttypes.h>

//#include <msp430f2013.h>
#include <msp430g2211.h>

#define DIGIT_1 BIT0 //    Common Cathode LEDs       //          ^ VCC                     ^ VCC
#define DIGIT_2 BIT1 //  +--1--A--F--2--3--B--+      //          |                         |
#define DIGIT_3 BIT2 //  | 4 x 7 Segment + DP |      //           \ Button_2                \ Button_1
#define DIGIT_4 BIT3 //  +--E--D--DP-C--G--4--+      //          |                         |
#define SR_A BIT4 // shift register serial data pin  //  P1.6 ---+----             P1.7 ---+
#define SR_CLK BIT5 // shift register clock pin      //          |    |/|                  |
#define BUTTON_2 BIT6                                //  220 nF ===   = | Piezo    220 nF ===
#define BUTTON_1 BIT7 //   --A--                     //          |    |\|                  |
//                    //  |     |                    //         ---  ---                  ---
#define _A ( 1 << 7 ) //  F     B                    //
#define _B ( 1 << 6 ) //  |     |                    //   RST --- 47 k pull-up (2.2 nF pull-down)
#define _C ( 1 << 5 ) //   --G--                     //  TEST --- leave open
#define _D ( 1 << 4 ) //  |     |                    //
#define _E ( 1 << 3 ) //  E     C                    //             [ ACTUAL CONFIGURATION ]
#define _F ( 1 << 2 ) //  |     |                    //          ^ VCC                        ^ VCC
#define _G ( 1 << 1 ) //   --D--  .DP                //          |                            |
#define DP ( 1 << 0 ) // decimal point               //           \ Button_2                   \ Button_1
static const uint8_t glyph_pattern[ 14 ] = {         //          |                            |
	_A | _B | _C | _D | _E | _F,      // 0           //  P1.6 ---+-------                     -
	_B | _C,                          // 1           //          |       |             100 R | |
	_A | _B | _D | _E | _G,           // 2           //  220 nF ===      |                    -
	_A | _B | _C | _D | _G,           // 3           //          |      ---                   |
	_B | _C | _F | _G,                // 4           //  Coil-   - /|   \|/ \  LED    P1.7 ---+
	_A | _C | _D | _F | _G,           // 5           // Speaker | | |   --- \v                |
	_A | _C | _D | _E | _F | _G,      // 6           // (40 R)   - \|    |   v        220 nF ===
	_A | _B | _C,                     // 7           //          |       |                    |
	_A | _B | _C | _D | _E | _F | _G, // 8           //         ---     ---                  ---
	_A | _B | _C | _D | _F | _G,      // 9
	0,                                // none
	_C | _D | _E | _G,                // o
	_C | _E | _G,                     // n
	_A | _E | _F | _G,                // F
};
#define GLYPH_none 10
#define GLYPH_o    11
#define GLYPH_n    12
#define GLYPH_O     0 // reuse 0 as O
#define GLYPH_F    13

#define CORRECTION 2
static const uint8_t glyph_delay[ 14 ] = {
	6 + CORRECTION, // 0
	2 + CORRECTION, // 1
	5 + CORRECTION, // 2
	5 + CORRECTION, // 3
	4 + CORRECTION, // 4
	5 + CORRECTION, // 5
	6 + CORRECTION, // 6
	3 + CORRECTION, // 7
	7 + CORRECTION, // 8
	6 + CORRECTION, // 9
	0 + CORRECTION, // none
	4 + CORRECTION, // o
	3 + CORRECTION, // n
	4 + CORRECTION, // F
};

static volatile uint8_t ticks = 0, seconds = 0, minutes = 0, hours = 0, days = 0;
static volatile uint8_t hour_point = DP;
static volatile uint8_t alarm_hour = 0, alarm_minute = 0;
static volatile uint8_t ticks_at_button_press = 0;
static volatile uint8_t displaying_watchdog = 0;
static volatile bool alarm_is_active = false;
static volatile bool go_to_sleep = false;
static volatile bool tick_happened = false;

enum TState { SLEEPING,
			  TIME_DISPLAYING, TIME_HOUR_EDITING, TIME_MINUTE_EDITING,
			  ALARM_IS_ACTIVE_DISPLAYING, ALARM_IS_ACTIVE_EDITING,
			  ALARM_DISPLAYING, ALARM_HOUR_EDITING, ALARM_MINUTE_EDITING,
			  SHINING, BUZZING };
static volatile TState state = TIME_DISPLAYING;

// f: 262  277  294  311  330  349  370  392  415  440  466  494  523  554  587  622  659  698  740  784  831  880  932  988  1047
// T: 3822 3608 3405 3214 3034 2863 2703 2551 2408 2273 2145 2025 1911 1804 1703 1607 1517 1432 1351 1276 1204 1136 1073 1012 956
// N: C4   C#4  D4   D#4  E4   F4   F#4  G4   G#4  A4   A#4  H4   C5   C#5  D5   D#5  E5   F5   F#5  G5   G#5  A5   A#5  H5   C6
#define _2  0xe0 // half
#define _4d 0xa0 // dotted quarter
#define _4  0x60 // quarter
#define _8d 0x40 // dotted eighth
#define _8  0x20 // eighth
#define _16 0x00 // sixteenth
#define PAUSE 0
#define C4    1
#define F4    2
#define G4    3
#define A4    4
#define B4    5
#define H4    6
#define C5    7
#define D5    8
static const uint16_t scale[ 9 ] = { 0,    // 0, Pause
									 3822, // 1, C4
									 2863, // 2, F4
									 2551, // 3, G4
									 2273, // 4, A4
									 2145, // 5, B4 (A#4)
									 2025, // 6, H4
									 1911, // 7, C5
									 1703, // 8, D5
};
static const uint8_t tune[ 39 ] = { // 0bDDDNNNNN -- D = duration, N = note (scale index)
	// http://www.youtube.com/watch?v=vGV8Hhhg9hQ
	_2|C5, _8|C5, _8|C5, _8|H4, _8|C5, _4|D5, _8|C5, _2|A4, _8|PAUSE,        //  4 seconds
	_4|B4, _4|B4, _8|B4, _8|B4, _8|A4, _8|B4, _4|C5, _8|B4, _2|G4, _8|PAUSE, //  8 seconds
	_4|A4, _8|G4, _4|F4, _4d|C4, _4|B4, _8|A4, _2|G4, _8|PAUSE,              // 12 seconds
	_2|C5, _8|C5, _8|C5, _8|C5, _8|B4, _2|A4, _4|PAUSE, _4|G4,               // 16 seconds
	_2|F4, _2|PAUSE, _2|PAUSE, _2|PAUSE,                                     // 20 seconds
};
static uint8_t tune_index;
static uint8_t remaining_duration;

static void sr_shift( uint8_t data )
{
	for ( uint8_t i = 0; i < 8; ++i ) {
		P1OUT &= ~SR_CLK;
        if ( data & 0x01 ) {
            P1OUT |= SR_A;
        } else {
            P1OUT &= ~SR_A;
        }
        data >>= 1;
		P1OUT |= SR_CLK;
	}
	P1OUT &= ~( SR_A | SR_CLK );
}

static void display_digit( uint8_t digit, uint8_t glyph_index, uint8_t decimal_point = 0 )
{
	P1OUT |= digit;
	sr_shift( glyph_pattern[ glyph_index ] | decimal_point );
	P1OUT &= ~digit;
	uint8_t on_duration = glyph_delay[ glyph_index ] + decimal_point;
	for ( uint8_t i = 0; i < on_duration; ++i ) {
		__delay_cycles( 100 );
	}
	P1OUT |= digit;
	for ( uint8_t i = 0; i < 8 + CORRECTION - on_duration; ++i ) {
		__delay_cycles( 100 );
	}
}

static void p_1_6_pwm_mode()
{
	P1DIR |= BIT6; // output
	P1OUT &= ~BIT6; // low
	P1REN &= ~BIT6; // disable resistor
	P1IFG &= ~BIT6; // Clear any pending interrupt flags
	P1IE &= ~BIT6; // disable button interrupt
	P1SEL |= BIT6; // enable Timer0_A Out1 function

	TACCTL1 = OUTMOD_7; // Reset/set  |~~|_____
	TACTL = TASSEL_2 | MC_1 | TACLR; // SMCLK + Up mode + Clear timer
}

static void p_1_6_input_mode()
{
	TACCR0 = 0; // period
	TACCR1 = 0; // pulse width
	TACTL = TASSEL_2 | MC_0 | TACLR; // SMCLK + Stop mode + Clear timer

	P1DIR &= ~BIT6; // input
	P1OUT &= ~BIT6; // select resistor to be pull-down
	P1REN |= BIT6; // enable resistor
	P1IES &= ~BIT6; // select the positive edge (low -> high transition) to cause an interrupt
	P1IFG &= ~BIT6; // Clear any pending interrupt flags
	P1IE |= BIT6; // enable button interrupt
	P1SEL &= ~BIT6; // disable Timer0_A Out1 function
}

static void config_registers()
{
	WDTCTL = WDTPW | WDTHOLD;

	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	//BCSCTL3 |= LFXT1S_2; // Use VLO as ACLK to test on eZ430 Stick
	BCSCTL3 |= LFXT1S_0 | XCAP_2; // Use Crystal as ACLK + 10.0 pF caps

	WDTCTL = WDT_ADLY_16; // Interval timer mode using ACLK clock source
	IE1 |= WDTIE;

	P1DIR |= DIGIT_1 | DIGIT_2 | DIGIT_3 | DIGIT_4 | SR_A | SR_CLK; // output
	P1DIR &= ~BUTTON_1; // input
	P1OUT &= ~BUTTON_1; // select resistor to be pull-down
	P1REN |= BUTTON_1; // enable resistor
	P1IES &= ~BUTTON_1; // select the positive edge (low -> high transition) to cause an interrupt
	P1IFG &= ~BUTTON_1; // Clear any pending interrupt flags
	P1IE |= BUTTON_1; // enable button interrupt

	P1OUT |= DIGIT_1 | DIGIT_2 | DIGIT_3 | DIGIT_4; // set all strobes high

	p_1_6_input_mode();
	sr_shift( 0 );
}

int main(void)
{
	config_registers();
	__enable_interrupt();

	while ( true ) {
		if ( go_to_sleep ) {
			go_to_sleep = false;
			state = SLEEPING;
			LPM3;
		}
		if ( tick_happened ) {
			tick_happened = false;
			if ( state == SHINING ) {
				// Triangle LED brightness ramping, if TACCR0 is set to 31:
				//( ticks >> 5 ) % 2 ? --TACCR1 : ++TACCR1; // relative
				// But we can also simply switch the LED on and off; TACCR0 must be set to 1:
				TACCR1 = seconds % 2 ? 0 : 2;
			}
			if ( state == BUZZING ) {
				if ( remaining_duration == 0 ) {
					TACCR1 = 0;
					TACCR0 = scale[ tune[ tune_index ] & 0x1f ];
					remaining_duration = ( ( tune[ tune_index ] & 0xe0 ) + 32 ) >> 2;
					++tune_index;
					if ( tune_index == sizeof( tune ) ) {
						tune_index = 0; // be kind, rewind :)
					}
				}
				TACCR1 += 16;
				--remaining_duration;
				//ticks % 2 ? TACCR0 <<= 1 : TACCR0 >>= 1; // arpeggio
				//if ( TACCR0 != 0 ) {
				//	ticks % 2 ? TACCR0 += 20 : TACCR0 -= 20; // tremolo
				//}
			}
		}
		if ( ( state == BUZZING && ticks > 32 ) ||
			 ( state == ALARM_IS_ACTIVE_EDITING && ( ( ticks - ticks_at_button_press + 64 ) % 64 > 32 ) ) )
		{
			continue;
		}
		uint8_t hour, minute, point;
		switch ( state ) {
		case TIME_DISPLAYING:
		case TIME_HOUR_EDITING:
		case TIME_MINUTE_EDITING:
		case SHINING:
		case BUZZING:
			hour = hours;
			minute = minutes;
			point = hour_point;
			break;
		case ALARM_DISPLAYING:
		case ALARM_HOUR_EDITING:
		case ALARM_MINUTE_EDITING:
			hour = alarm_hour;
			minute = alarm_minute;
			point = DP;
			break;
		}
		if ( state == ALARM_IS_ACTIVE_DISPLAYING || state == ALARM_IS_ACTIVE_EDITING ) {
			if ( alarm_is_active ) {
				display_digit( DIGIT_1, GLYPH_none );
				display_digit( DIGIT_2, GLYPH_none );
				display_digit( DIGIT_3, GLYPH_o );
				display_digit( DIGIT_4, GLYPH_n, DP );
			} else {
				display_digit( DIGIT_1, GLYPH_none );
				display_digit( DIGIT_2, GLYPH_O );
				display_digit( DIGIT_3, GLYPH_F );
				display_digit( DIGIT_4, GLYPH_F );
			}
		} else {
			uint8_t digit_1 = hour / 10;
			uint8_t digit_2 = hour % 10;
			uint8_t digit_3 = minute / 10;
			uint8_t digit_4 = minute % 10;
			if ( ( state == TIME_HOUR_EDITING || state == ALARM_HOUR_EDITING ) &&
				 ( ( ticks - ticks_at_button_press + 64 ) % 64 > 32 ) )
			{
				digit_1 = digit_2 = GLYPH_none;
			} else if ( digit_1 == 0 ) {
				digit_1 = GLYPH_none;
			}
			if ( ( state == TIME_MINUTE_EDITING || state == ALARM_MINUTE_EDITING ) &&
				 ( ( ticks - ticks_at_button_press + 64 ) % 64 > 32 ) )
			{
				digit_3 = digit_4 = GLYPH_none;
			}
			if ( ! go_to_sleep ) {
				display_digit( DIGIT_1, digit_1 );
				display_digit( DIGIT_2, digit_2, point );
				display_digit( DIGIT_3, digit_3 );
				display_digit( DIGIT_4, digit_4, alarm_is_active ? DP : 0 );
			}
		}
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
	displaying_watchdog = 0;
	if ( P1IFG & BUTTON_1 ) {
		switch ( state ) {
		case SLEEPING:
			state = TIME_DISPLAYING;
			LPM3_EXIT;
			break;
		case TIME_DISPLAYING:
			state = alarm_is_active ? ALARM_DISPLAYING : ALARM_IS_ACTIVE_DISPLAYING;
			break;
		case ALARM_IS_ACTIVE_DISPLAYING:
		case ALARM_DISPLAYING:
			go_to_sleep = true;
			break;
		case TIME_HOUR_EDITING:
			hours = ++hours % 24;
			break;
		case TIME_MINUTE_EDITING:
			minutes = ++minutes % 60;
			seconds = 0;
			ticks = 0;
			hour_point = DP;
			break;
		case ALARM_IS_ACTIVE_EDITING:
			alarm_is_active ^= 1;
			break;
		case ALARM_HOUR_EDITING:
			alarm_hour = ++alarm_hour % 24;
			break;
		case ALARM_MINUTE_EDITING:
			alarm_minute = ( alarm_minute + 5 ) % 60;
			break;
		case SHINING:
		case BUZZING:
			p_1_6_input_mode();
			go_to_sleep = true;
			break;
		}
		ticks_at_button_press = ticks;
		P1IFG &= ~BUTTON_1; // clear the interrupt flag
	} else if ( P1IFG & BUTTON_2 ) {
		switch ( state ) {
		case SLEEPING:
			// no reaction
			break;
		case TIME_DISPLAYING:
			state = TIME_HOUR_EDITING;
			break;
		case TIME_HOUR_EDITING:
			state = TIME_MINUTE_EDITING;
			break;
		case TIME_MINUTE_EDITING:
			state = TIME_DISPLAYING;
			break;
		case ALARM_IS_ACTIVE_DISPLAYING:
		case ALARM_DISPLAYING:
			state = ALARM_IS_ACTIVE_EDITING;
			break;
		case ALARM_IS_ACTIVE_EDITING:
			state = alarm_is_active ? ALARM_HOUR_EDITING : ALARM_IS_ACTIVE_DISPLAYING;
			break;
		case ALARM_HOUR_EDITING:
			state = ALARM_MINUTE_EDITING;
			break;
		case ALARM_MINUTE_EDITING:
			state = ALARM_IS_ACTIVE_DISPLAYING;
			break;
		}
		ticks_at_button_press = ( ticks + 48 ) % 64;
		P1IFG &= ~BUTTON_2; // clear the interrupt flag
	} else {
		P1IFG = 0; // Probably unnecessary, but if another flag occurs in P1, this will clear it.
	}
}

#pragma vector = WDT_VECTOR
__interrupt void WATCHDOG_INTERVAL_TIMER_ISR(void)
{
	// Flag is cleared automatically.
	tick_happened = true;
	++ticks;
	switch ( ticks ) {
	case 32:
		hour_point = 0;
		break;
	case 64:
		hour_point = DP;
		ticks = 0;
		++seconds;
		if ( state == TIME_DISPLAYING || state == ALARM_IS_ACTIVE_DISPLAYING || state == ALARM_DISPLAYING ) {
			++displaying_watchdog;
			//if ( displaying_watchdog > ( hours >= 22 || hours < 7 ? 3 : 60 ) ) {
			if ( displaying_watchdog > 3 ) {
				go_to_sleep = true;
			}
		}
		if ( seconds == 60 ) {
			seconds = 0;
			++minutes;
			if ( minutes == 60 ) {
				minutes = 0;
				++hours;
				if ( hours == 24 ) {
					hours = 0;
					//seconds = 2; // correction for too slow quarz
					//++days;
				}
			}
			if ( alarm_is_active && hours == alarm_hour && minutes == alarm_minute ) {
				state = SHINING; // Let your geek (and the LED) shine.
				p_1_6_pwm_mode();
				TACCR1 = 2; // 2 is permanent on, 0 is off when TACCR0 is 1.
				TACCR0 = 1;
				LPM3_EXIT;
			} else if ( state == SHINING ) {
				state = BUZZING; // Play a delightful tune.
				tune_index = remaining_duration = 0;
			} else if ( state == BUZZING ) {
				p_1_6_input_mode(); // All attempts were in vain.
				go_to_sleep = true;
			}
		}
		break;
	}
}

//if ( days == 32 ||
//	 days == 31 && ( months == 4 || months == 6 || months == 9 || months == 11 ) ||
//	 days == 30 && months == 2 && leap_year != 0 ||
//	 days == 29 && months == 2 && leap_year == 0 )
//{
//	days = 1;
//	++months;
//	if ( months == 13 ) {
//		months = 1;
//		++years;
//		if ( years % 400 == 0 ||
//			 years % 4 == 0 && years % 100 != 0 )
//		{
//			leap_year = 1;
//		} else {
//			leap_year = 0;
//		}
//	}
//}
