

#ifndef TMC5160_REGISTERS_H
#define TMC5160_REGISTERS_H
#include "arduino.h"

#pragma once
#pragma pack(push, 1)

static constexpr uint8_t IC_VERSION = 0x30;
static constexpr uint32_t DEFAULT_F_CLK = 12000000;  ///< Typical internal clock frequency in Hz.
static constexpr uint16_t _uStepCount = 256;  // Number of microsteps per step

//Register address
const static uint8_t ADDRESS_GCONF           = 0x00; ///< Global configuration flags
const static uint8_t ADDRESS_GSTAT           = 0x01; ///< Global status flags
const static uint8_t ADDRESS_IFCNT           = 0x02; ///< UART transmission counter
const static uint8_t ADDRESS_SLAVECONF       = 0x03; ///< UART slave configuration
const static uint8_t ADDRESS_IO_INPUT_OUTPUT = 0x04; ///< Read input / write output pins
const static uint8_t ADDRESS_X_COMPARE       = 0x05; ///< Position comparison register
const static uint8_t ADDRESS_OTP_PROG        = 0x06; ///< OTP programming register
const static uint8_t ADDRESS_OTP_READ        = 0x07; ///< OTP read register
const static uint8_t ADDRESS_FACTORY_CONF    = 0x08; ///< Factory configuration (clock trim)
const static uint8_t ADDRESS_SHORT_CONF      = 0x09; ///< Short detector configuration
const static uint8_t ADDRESS_DRV_CONF        = 0x0A; ///< Driver configuration
const static uint8_t ADDRESS_GLOBAL_SCALER   = 0x0B; ///< Global scaling of motor current
const static uint8_t ADDRESS_OFFSET_READ     = 0x0C; ///< Offset calibration results

// Velocity dependent driver feature control registers
const static uint8_t ADDRESS_IHOLD_IRUN = 0x10; ///< Driver current control
const static uint8_t ADDRESS_TPOWERDOWN = 0x11; ///< Delay before power down
const static uint8_t ADDRESS_TSTEP      = 0x12; ///< Actual time between microsteps
const static uint8_t ADDRESS_TPWMTHRS   = 0x13; ///< Upper velocity for stealthChop voltage PWM mode
const static uint8_t ADDRESS_TCOOLTHRS  = 0x14; ///< Lower threshold velocity for switching on smart energy coolStep and stallGuard feature
const static uint8_t ADDRESS_THIGH      = 0x15; ///< Velocity threshold for switching into a different chopper mode and fullstepping

// Ramp generator motion control registers
const static uint8_t ADDRESS_RAMPMODE = 0x20; ///< Driving mode (Velocity, Positioning, Hold)
const static uint8_t ADDRESS_XACTUAL  = 0x21; ///< Actual motor position
const static uint8_t ADDRESS_VACTUAL  = 0x22; ///< Actual motor velocity from ramp generator
const static uint8_t ADDRESS_VSTART   = 0x23; ///< Motor start velocity
const static uint8_t ADDRESS_A_1      = 0x24; ///< First acceleration between ADDRESS_VSTART and V1
const static uint8_t ADDRESS_V_1      = 0x25; ///< First acceleration/deceleration phase target velocity
const static uint8_t ADDRESS_AMAX     = 0x26; ///< Second acceleration between V1 and ADDRESS_VMAX
const static uint8_t ADDRESS_VMAX     = 0x27; ///< Target velocity in velocity mode
const static uint8_t ADDRESS_DMAX     = 0x28; ///< Deceleration between ADDRESS_VMAX and V1
const static uint8_t ADDRESS_D_1      = 0x2A; ///< Deceleration between V1 and ADDRESS_VSTOP
// Attention: Do not set 0 in positioning mode, even if V1=0!
const static uint8_t ADDRESS_VSTOP = 0x2B; ///< Motor stop velocity
// Attention: Set ADDRESS_VSTOP > ADDRESS_VSTART!
// Attention: Do not set 0 in positioning mode, minimum 10 recommend!
const static uint8_t ADDRESS_TZEROWAIT = 0x2C; ///< Waiting time after ramping down to zero velocity before next movement or direction inversion can start.
const static uint8_t ADDRESS_XTARGET   = 0x2D; ///< Target position for ramp mode

// Ramp generator driver feature control registers
const static uint8_t ADDRESS_VDCMIN    = 0x33; ///< Velocity threshold for enabling automatic commutation dcStep
const static uint8_t ADDRESS_SW_MODE   = 0x34; ///< Switch mode configuration
const static uint8_t ADDRESS_RAMP_STAT = 0x35; ///< Ramp status and switch event status
const static uint8_t ADDRESS_XLATCH    = 0x36; ///< Ramp generator latch position upon programmable switch event

// Encoder registers
const static uint8_t ADDRESS_ENCMODE    = 0x38; ///< Encoder configuration and use of N channel
const static uint8_t ADDRESS_X_ENC      = 0x39; ///< Actual encoder position
const static uint8_t ADDRESS_ENC_CONST  = 0x3A; ///< Accumulation constant
const static uint8_t ADDRESS_ENC_STATUS = 0x3B; ///< Encoder status information
const static uint8_t ADDRESS_ENC_LATCH  = 0x3C; ///< Encoder position latched on N event
const static uint8_t ADDRESS_ENC_DEVIATION = 0x3D; ///< Maximum number of steps deviation between encoder counter and ADDRESS_XACTUAL for deviation warning

// Motor driver registers
const static uint8_t ADDRESS_MSLUT_0_7 = 0x60;  ///< Microstep table entries. Add 0...7 for the next registers
const static uint8_t ADDRESS_MSLUTSEL = 0x68;   ///< Look up table segmentation definition
const static uint8_t ADDRESS_MSLUTSTART = 0x69; ///< Absolute current at microstep table entries 0 and 256
const static uint8_t ADDRESS_MSCNT = 0x6A;      ///< Actual position in the microstep table
const static uint8_t ADDRESS_MSCURACT = 0x6B;   ///< Actual microstep current
const static uint8_t ADDRESS_CHOPCONF = 0x6C;   ///< Chopper and driver configuration
const static uint8_t ADDRESS_COOLCONF = 0x6D;   ///< coolStep smart current control register and stallGuard2 configuration
const static uint8_t ADDRESS_DCCTRL = 0x6E;     ///< dcStep automatic commutation configuration register
const static uint8_t ADDRESS_DRV_STATUS = 0x6F; ///< stallGuard2 value and driver error flags
const static uint8_t ADDRESS_PWMCONF = 0x70;    ///< stealthChop voltage PWM mode chopper configuration
const static uint8_t ADDRESS_PWM_SCALE = 0x71;  ///< Results of stealthChop amplitude regulator.
const static uint8_t ADDRESS_PWM_AUTO = 0x72;   ///< Automatically determined PWM config values
const static uint8_t ADDRESS_LOST_STEPS = 0x73; ///< Number of input steps skipped due to dcStep. only with SD_MODE = 1

// General Configuration Registers
union GCONF_Register {
    struct {
        uint32_t recalibrate            : 1; ///< Recalibrate on driver disable due to zero crossing
        uint32_t faststandstill         : 1; ///< Timeout for step execution until standstill detection
        uint32_t en_pwm_mode            : 1; ///< Enable stealthChop voltage PWM mode
        uint32_t multistep_filt         : 1; ///< Enable step input filtering for stealthChop with external step source
        uint32_t shaft                  : 1; ///< Set motor direction as normal or inverse
        uint32_t diag0_error            : 1; ///< Activate DIAG0 on driver errors: Over temperature (ot), short to GND (s2g), undervoltage chargepump (uv_cp)
        uint32_t diag0_otpw             : 1; ///< Activate DIAG0 on driver over temperature prewarning (otpw)
        uint32_t diag0_stall_step       : 1; ///< SD_MODE=1: Activate DIAG0 on motor stall. SD_MODE=0: Use DIAG0 as STEP output
        uint32_t diag1_stall_dir        : 1; ///< SD_MODE=1: Activate DIAG1 on motor stall. SD_MODE=0: Use DIAG1 as DIR output
        uint32_t diag1_index            : 1; ///< Activate DIAG1 on index position
        uint32_t diag1_onstate          : 1; ///< Activate DIAG1 when chopper is on
        uint32_t diag1_steps_skipped    : 1; ///< Toggle output when steps are skipped in dcStep mode
        uint32_t diag0_int_pushpull     : 1; ///< Enable SWN_DIAG0 push-pull output
        uint32_t diag1_poscomp_pushpull : 1; ///< Enable SWP_DIAG1 push-pull output
        uint32_t small_hysteresis       : 1; ///< Set small hysteresis for step frequency comparison
        uint32_t stop_enable            : 1; ///< Enable emergency stop: ENCA_DCIN stops sequencer when tied high
        uint32_t direct_mode            : 1; ///< Enable direct motor current and polarity control
        uint32_t test_mode              : 1; ///< Not intended for normal use
    };
    uint32_t bytes;
};

// Global Status Registers
union GSTAT_Register {
    struct
    {
        uint32_t reset    : 1;   ///< Indicates IC reset since last ADDRESS_GSTAT read
        uint32_t drv_err  : 1;   ///< Indicates driver shutdown due to overtemperature or short circuit
        uint32_t uv_cp    : 1;   ///< Indicates undervoltage on charge pump, disabling the driver
        uint32_t reserved : 29;  ///< Reserved bits for future use
    };
    uint32_t bytes;
};

// UART Slave Configuration
union SLAVECONF_Register {
    struct {
        uint32_t slaveaddr : 8;   ///< Address of unit for the UART interface. The address increments by one when external address pin NAI is active.
        uint32_t senddelay : 4;   ///< Number of bit times before replying to a register read in UART mode. Set > 1 with multiple slaves.
        uint32_t reserved  : 20;  ///< Reserved bits for future use
    };
    uint32_t bytes;
};


// IO Input Configuration
union IOIN_Register {
    struct {
        uint32_t refl_step      : 1;   ///< Reflects the status of the external level at the STEP input
        uint32_t refr_dir       : 1;   ///< Reflects the status of the external level at the DIR input
        uint32_t encb_dcen_cfg4 : 1;   ///< Reflects the status of the DCEN_CFG4 input
        uint32_t enca_dcin_cfg5 : 1;   ///< Reflects the status of the DCIN_CFG5 input
        uint32_t drv_enn        : 1;   ///< Reflects the status of the external level at the nENBL input
        uint32_t enc_n_dco_cfg6 : 1;   ///< Reflects the status of the DCO_CFG6 input
        uint32_t sd_mode        : 1;   ///< 1=External step and dir source
        uint32_t swcomp_in      : 1;   ///< Reflects the status of the external level at the SWCOMP_IN input
        uint32_t reserved       : 15;  ///< Reserved bits for future use
        uint32_t version        : 8;   ///< Version information
    };
    uint32_t bytes;
};


// OTP Programming
union OTP_PROG_Register {
    struct {
        uint32_t otpbit    : 3;   ///< Selection of OTP bit to be programmed
        uint32_t otpbyte   : 2;   ///< Selection of OTP byte. Set to 00
        uint32_t reserved  : 3;   ///< Reserved bits
        uint32_t otpmagic  : 8;   ///< Set to 0xBD to program
        uint32_t reserved2 : 16;  ///< Reserved bits for future use
    };
    uint32_t bytes;
};

// OTP Configuration Memory
union OTP_READ_Register {
    struct {
        uint32_t otp_fclktrim : 5;  ///< Reset default for FCLKTRIM (frequency source calibration)
        uint32_t otp_S2_level : 1;  ///< Reset default for Short detection levels
        uint32_t otp_bbm      : 1;  ///< Reset default for DRVCONF.BBMCLKS
        uint32_t otp_tbl      : 1;  ///< Reset default for TBL
        uint32_t reserved     : 24; ///< Reserved bits for future use
    };
    uint32_t bytes;
};

// Short Detector Configuration
union SHORT_CONF_Register {
    struct {
        uint32_t s2vs_level  : 4;   ///< Short to VS detector for low side FETs sensitivity
        uint32_t reserved1   : 4;   ///< Reserved bits
        uint32_t s2g_level   : 4;   ///< Short to GND detector for high side FETs sensitivity
        uint32_t reserved2   : 2;   ///< Reserved bits
        uint32_t shortfilter : 2;   ///< Spike filtering bandwidth for short detection
        uint32_t shortdelay  : 1;   ///< Short detection delay
        uint32_t reserved3   : 15;  ///< Reserved bits for future use
    };
    uint32_t bytes;
};


// Driver Configuration
union DRV_CONF_Register {
    struct {
        uint32_t bbmtime     : 5;  ///< Break before make delay (0 to 24)
        uint32_t reserved1   : 3;  ///< Reserved bits
        uint32_t bbmclks     : 4;  ///< Digital BBM Time in clock cycles
        uint32_t otselect    : 2;  ///< Selection of over temperature level for bridge disable
        uint32_t drvstrength : 2;  ///< Selection of gate drivers current
        uint32_t filt_isense : 2;  ///< Filter time constant of sense amplifier to suppress ringing and coupling from second coil operation
        uint32_t reserved2   : 14; ///< Reserved bits for future use
    };
    uint32_t bytes;
};


// Offset Calibration Result
union OFFSET_READ_Register {
    struct {
        uint32_t phase_b  : 8;  ///< Offset calibration result for phase B
        uint32_t phase_a  : 8;  ///< Offset calibration result for phase A
        uint32_t reserved : 16; ///< Reserved bits for future use
    };
    uint32_t bytes;
};

// Driver Current Control
union IHOLD_IRUN_Register {
    struct {
        uint32_t ihold      : 5;  ///< Standstill current (0=1/32...31=32/32)
        uint32_t reserved1  : 3;  ///< Reserved bits
        uint32_t irun       : 5;  ///< Motor run current (0=1/32...31=32/32). Should be between 16 and 31 for best performance.
        uint32_t reserved2  : 3;  ///< Reserved bits
        uint32_t iholddelay : 4;  ///< Controls the number of clock cycles for motor power down when entering standstill
        uint32_t reserved3  : 12; ///< Reserved bits for future use
    };
    uint32_t bytes;
};


// Switch Mode Configuration
union SW_MODE_Register {
    struct {
        uint32_t stop_l_enable    : 1;  ///< Enable automatic motor stop during active left reference switch input
        uint32_t stop_r_enable    : 1;  ///< Enable automatic motor stop during active right reference switch input
        uint32_t pol_stop_l       : 1;  ///< Sets the active polarity of the left reference switch input (1=inverted, low active, a low level on REFL stops the motor)
        uint32_t pol_stop_r       : 1;  ///< Sets the active polarity of the right reference switch input (1=inverted, low active, a low level on REFR stops the motor)
        uint32_t swap_lr          : 1;  ///< Swap the left and the right reference switch inputs
        uint32_t latch_l_active   : 1;  ///< Activate latching of the position to ADDRESS_XLATCH upon an active going edge on REFL
        uint32_t latch_l_inactive : 1;  ///< Activate latching of the position to ADDRESS_XLATCH upon an inactive going edge on REFL
        uint32_t latch_r_active   : 1;  ///< Activate latching of the position to ADDRESS_XLATCH upon an active going edge on REFR
        uint32_t latch_r_inactive : 1;  ///< Activate latching of the position to ADDRESS_XLATCH upon an inactive going edge on REFR
        uint32_t en_latch_encoder : 1;  ///< Latch encoder position to ADDRESS_ENC_LATCH upon reference switch event
        uint32_t sg_stop          : 1;  ///< Enable stop by stallGuard2 (also available in dcStep mode). Disable to release motor after stop event.
        uint32_t en_softstop      : 1;  ///< Enable soft stop upon a stop event (uses the deceleration ramp settings)
        uint32_t reserved         : 21; ///< Reserved bits for future use
    };
    uint32_t bytes;
};

// Ramp Status and Switch Event Status
union RAMP_STAT_Register {
    struct {
        uint32_t status_stop_l     : 1;  ///< Reference switch left status (1=active)
        uint32_t status_stop_r     : 1;  ///< Reference switch right status (1=active)
        uint32_t status_latch_l    : 1;  ///< Latch left ready (enable position latching using SWITCH_MODE settings latch_l_active or latch_l_inactive)
        uint32_t status_latch_r    : 1;  ///< Latch right ready (enable position latching using SWITCH_MODE settings latch_r_active or latch_r_inactive)
        uint32_t event_stop_l      : 1;  ///< Signals an active stop left condition due to stop switch.
        uint32_t event_stop_r      : 1;  ///< Signals an active stop right condition due to stop switch.
        uint32_t event_stop_sg     : 1;  ///< Signals an active StallGuard2 stop event.
        uint32_t event_pos_reached : 1;  ///< Signals that the target position has been reached (position_reached becoming active).
        uint32_t velocity_reached  : 1;  ///< Signals that the target velocity is reached.
        uint32_t position_reached  : 1;  ///< Signals that the target position is reached.
        uint32_t vzero             : 1;  ///< Signals that the actual velocity is 0.
        uint32_t t_zerowait_active : 1;  ///< Signals that TZEROWAIT is active after a motor stop. During this time, the motor is in standstill.
        uint32_t second_move       : 1;  ///< Signals that the automatic ramp required moving back in the opposite direction
        uint32_t status_sg         : 1;  ///< Signals an active stallGuard2 input from the coolStep driver or from the dcStep unit, if enabled.
        uint32_t reserved          : 19; ///< Reserved bits for future use
    };
    uint32_t bytes;
};



// Encoder Configuration and Use of N Channel
union ENCMODE_Register {
    struct {
        uint32_t pol_A           : 1;  ///< Required A polarity for an N channel event (0=neg., 1=pos.)
        uint32_t pol_B           : 1;  ///< Required B polarity for an N channel event (0=neg., 1=pos.)
        uint32_t pol_N           : 1;  ///< Defines active polarity of N (0=low active, 1=high active)
        uint32_t ignore_AB       : 1;  ///< Ignore A and B polarity for N channel event
        uint32_t clr_cont        : 1;  ///< Always latch or latch and clear ADDRESS_X_ENC upon an N event
        uint32_t clr_once        : 1;  ///< Latch or latch and clear ADDRESS_X_ENC on the next N event following the write access
        uint32_t sensitivity     : 2;  ///< N channel event sensitivity
        uint32_t reserved1       : 1;  ///< Reserved bit
        uint32_t clr_enc_x       : 1;  ///< Clear encoder counter ADDRESS_X_ENC upon N-event
        uint32_t latch_x_act     : 1;  ///< Also latch ADDRESS_XACTUAL position together with ADDRESS_X_ENC.
        uint32_t enc_sel_decimal : 1;  ///< Encoder prescaler divisor binary mode (0) / decimal mode (1)
        uint32_t reserved2       : 20; ///< Reserved bits for future use
    };
    uint32_t bytes;
};



// Encoder Status Information
union ENC_STATUS_Register {
    struct {
        uint32_t n_event        : 1;  ///< N event detected
        uint32_t deviation_warn : 1;  ///< Deviation between X_ACTUAL and ADDRESS_X_ENC detected
        uint32_t reserved       : 30; ///< Reserved bits for future use
    };
    uint32_t bytes;
};


// Chopper and Driver Configuration
union CHOPCONF_Register {
    struct {
        uint32_t toff        : 4;  ///< Off time setting controls duration of slow decay phase. 0 : Driver disabled.
        uint32_t hstrt_tfd   : 3;  ///< chm=0: hysteresis start value HSTRT, chm=1: fast decay time setting bits 0:2
        uint32_t hend_offset : 4;  ///< chm=0: hysteresis low value HEND, chm=1: sine wave offset
        uint32_t tfd_3       : 1;  ///< chm=1: fast decay time setting bit 3
        uint32_t disfdcc     : 1;  ///< chm=1: disable current comparator usage for termination of the fast decay cycle
        uint32_t rndtf       : 1;  ///< Enable random modulation of chopper TOFF time
        uint32_t chm         : 1;  ///< Chopper mode (0=standard - spreadCycle ; 1=constant off time with fast decay time)
        uint32_t tbl         : 2;  ///< Comparator blank time select.
        uint32_t vsense      : 1;  ///< Select resistor voltage sensitivity (0=Low sensitivity ; 1=High sensitivity)
        uint32_t vhighfs     : 1;  ///< Enable switching to fullstep when VHIGH is exceeded.
        uint32_t vhighchm    : 1;  ///< Enable switching to chm=1 and fd=0 when VHIGH is exceeded
        uint32_t tpfd        : 4;  ///< Passive fast decay time
        uint32_t mres        : 4;  ///< Set microstep resolution
        uint32_t intpol      : 1;  ///< Enable interpolation to 256 microsteps with an external motion controller
        uint32_t dedge       : 1;  ///< Enable double edge step pulses
        uint32_t diss2g      : 1;  ///< Disable short to GND protection
        uint32_t diss2vs     : 1;  ///< Disable short to supply protection
        uint32_t reserved    : 1;  ///< Reserved bit for future use
    };
    uint32_t bytes;
};


// coolStep Smart Current Control and StallGuard2 Configuration
union COOLCONF_Register {
    struct {
        uint32_t semin     : 4;  ///< Minimum stallGuard2 value for smart current control and smart current enable
        uint32_t reserved1 : 1;  ///< Reserved bit
        uint32_t seup      : 2;  ///< Current increment step width
        uint32_t semax     : 4;  ///< stallGuard2 hysteresis value for smart current control
        uint32_t sedn      : 2;  ///< Current decrement step speed
        uint32_t seimin    : 1;  ///< Minimum current for smart current control
        uint32_t sgt       : 7;  ///< stallGuard2 threshold value
        uint32_t reserved2 : 7;  ///< Reserved bits
        uint32_t sfilt     : 1;  ///< Enable stallGuard2 filter
        uint32_t reserved3 : 5;  ///< Reserved bits for future use
    };
    uint32_t bytes;
};


// dcStep Automatic Commutation Configuration Register
union DCCTRL_Register {
    struct {
        uint32_t dc_time   : 10; ///< Upper PWM on time limit for commutation
        uint32_t reserved  : 6;  ///< Reserved bits
        uint32_t dc_sg     : 8;  ///< Max. PWM on time for step loss detection using dcStep stallGuard2 in dcStep mode.
        uint32_t reserved2 : 8;  ///< Reserved bits for future use
    };
    uint32_t bytes;
};

// stallGuard2 Value and Driver Error Flags

union DRV_STATUS_Register {
    struct {
        uint32_t sg_result  : 9;   ///< stallGuard2 result or motor temperature estimation in standstill
        uint32_t reserved1  : 3;   ///< Reserved bits
        uint32_t s2vsa      : 1;   ///< Short to supply indicator phase A
        uint32_t s2vsb      : 1;   ///< Short to supply indicator phase B
        uint32_t stealth    : 1;   ///< stealthChop indicator
        uint32_t fsactive   : 1;   ///< Full step active indicator
        uint32_t reserved2  : 7;   ///< Reserved bits
        uint32_t cs_actual  : 5;   ///< Actual motor current / smart energy current
        uint32_t reserved3  : 3;   ///< Reserved bits
        uint32_t stallguard : 1;   ///< stallGuard2 status
        uint32_t ot         : 1;   ///< Overtemperature flag
        uint32_t otpw       : 1;   ///< Overtemperature pre-warning flag
        uint32_t s2ga       : 1;   ///< Short to ground indicator phase A
        uint32_t s2gb       : 1;   ///< Short to ground indicator phase B
        uint32_t ola        : 1;   ///< Open load indicator phase A
        uint32_t olb        : 1;   ///< Open load indicator phase B
        uint32_t stst       : 1;   ///< Standstill indicator
    };
    uint32_t bytes;
};


// stealthChop Voltage PWM Mode Chopper Configuration

union PWMCONF_Register {
    struct {
        uint32_t pwm_ofs       : 8;   ///< User-defined PWM amplitude (offset)
        uint32_t pwm_grad      : 8;   ///< User-defined PWM amplitude (gradient)
        uint32_t pwm_freq      : 2;   ///< PWM frequency selection
        uint32_t pwm_autoscale : 1;   ///< Enable PWM automatic amplitude scaling
        uint32_t pwm_autograd  : 1;   ///< PWM automatic gradient adaptation
        uint32_t reserved1     : 2;   ///< Reserved bits
        uint32_t freewheel     : 2;   ///< Standstill option when motor current setting is zero (I_HOLD=0).
        uint32_t reserved2     : 2;   ///< Reserved bits
        uint32_t pwm_reg       : 4;   ///< Regulation loop gradient
        uint32_t pwm_lim       : 4;   ///< PWM automatic scale amplitude limit when switching on
    };
    uint32_t bytes;
};


// Results of stealthChop Amplitude Regulator

union PWM_SCALE_Register {
    struct {
        uint32_t pwm_scale_sum  : 8;  ///< Actual PWM duty cycle
        uint32_t reserved1      : 8;  ///< Reserved bits
        uint32_t pwm_scale_auto : 9;  ///< Result of the automatic amplitude regulation based on current measurement.
        uint32_t reserved2      : 7;  ///< Reserved bits
    };
    uint32_t bytes;
};

// stealthChop Automatically Generated Values Read Out

union PWM_AUTO_Register {
    struct {
        uint32_t pwm_ofs_auto  : 8;  ///< Automatically determined offset value
        uint32_t reserved1     : 8;  ///< Reserved bits
        uint32_t pwm_grad_auto : 8;  ///< Automatically determined gradient value
        uint32_t reserved2     : 8;  ///< Reserved bits
    };
    uint32_t bytes;
};

// Register Field Values
enum RAMPMODE_Values {
    POSITIONING_MODE1  = 0x00,   ///< Using all A, D, and V parameters
    VELOCITY_MODE_POS = 0x01,   ///< Positive ADDRESS_VMAX, using ADDRESS_AMAX acceleration
    VELOCITY_MODE_NEG = 0x02,   ///< Negative ADDRESS_VMAX, using ADDRESS_AMAX acceleration
    HOLD_MODE1         = 0x03    ///< Velocity remains unchanged, unless a stop event occurs
};

enum PWMCONF_freewheel_Values {
    FREEWHEEL_NORMAL   = 0x00, ///< Normal operation
    FREEWHEEL_ENABLED  = 0x01, ///< Freewheeling
    FREEWHEEL_SHORT_LS = 0x02, ///< Coil shorted using LS drivers
    FREEWHEEL_SHORT_HS = 0x03  ///< Coil shorted using HS drivers
};

enum ENCMODE_sensitivity_Values {
    ENCODER_N_NO_EDGE       = 0x00, ///< N channel active while the N event is valid
    ENCODER_N_RISING_EDGE   = 0x01, ///< N channel active when the N event is activated
    ENCODER_N_FALLING_EDGE  = 0x02, ///< N channel active when the N event is de-activated
    ENCODER_N_BOTH_EDGES    = 0x03  ///< N channel active on N event activation and de-activation
};
#pragma pack(pop)

#endif
