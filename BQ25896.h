#ifndef __BQ25896_H__
#define __BQ25896_H__

#include "mbed.h"

//typedef uint8_t uint8_t;

const uint8_t BQ25896_I2C_ADDR = 0x6B ;

class BQ25896
{
public:
    //static const uint8_t I2C_ADDR;
    // register names
    // datasheet, p 32
    struct REGISTER
    {
    public:
        struct REG00
        {
            static const uint8_t _ADDR = 0x00;

            static const uint8_t EN_HIZ = 0x80;
            static const uint8_t EN_ILIM = 0x40;
            static const uint8_t IINLIM = 0x3F;
        };

        struct REG01
        {
            static const uint8_t _ADDR = 0x01;

            static const uint8_t BHOT = 0xC0;
            static const uint8_t BCOLD = 0x20;
            static const uint8_t VINDPM_OS = 0x1F;
        };

        struct REG02
        {
            static const uint8_t _ADDR = 0x02;

            static const uint8_t CONV_START = 0x80;
            static const uint8_t CONV_RATE = 0x40;
            static const uint8_t BOOST_FREQ = 0x20;
            static const uint8_t ICO_EN = 0x10;
            static const uint8_t FORCE_DPDM = 0x02;
            static const uint8_t AUTO_DPDM_EN = 0x01;
        };

        struct REG03
        {
            static const uint8_t _ADDR = 0x03;

            static const uint8_t BAT_LOADEN = 0x80;
            static const uint8_t WD_RST = 0x40;
            static const uint8_t OTG_CONFIG = 0x20;
            static const uint8_t CHG_CONFIG = 0x10;
            static const uint8_t SYS_MIN = 0x0E;
            static const uint8_t MIN_VBAT_SEL = 0x01;
        };

        struct REG04
        {
            static const uint8_t _ADDR = 0x04;

            static const uint8_t EN_PUMPX = 0x80;
            static const uint8_t ICHG = 0x7F;
        };

        struct REG05
        {
            static const uint8_t _ADDR = 0x05;

            static const uint8_t IPRECHG = 0xF0;
            static const uint8_t ITERM = 0x0F;
        };

        struct REG06
        {
            static const uint8_t _ADDR = 0x06;

            static const uint8_t VREG = 0xFC;
            static const uint8_t BATLOWV = 0x02;
            static const uint8_t VRECHG = 0x01;
        };

        struct REG07
        {
            static const uint8_t _ADDR = 0x07;

            static const uint8_t EN_TERM = 0x80;
            static const uint8_t STAT_DIS = 0x40;
            static const uint8_t WATCHDOG = 0x30;
            static const uint8_t EN_TIMER = 0x08;
            static const uint8_t CHG_TIMER = 0x06;
            static const uint8_t JEITA_ISET = 0x01;
        };

        struct REG08
        {
            static const uint8_t _ADDR = 0x08;
        };

        struct REG09
        {
            static const uint8_t _ADDR = 0x09;
        };

        struct REG0A
        {
            static const uint8_t _ADDR = 0x0a;

            static const uint8_t BOOSTV = 0xF0;
            static const uint8_t PFM_OTG_DIS = 0x08;
            static const uint8_t BOOST_LIM = 0x07;
        };

        struct REG0B
        {
            static const uint8_t _ADDR = 0x0b;

            static const uint8_t VBUS_STAT = 0xE0;
            static const uint8_t CHRG_STAT = 0x18;
            static const uint8_t PG_STAT = 0x04;
            static const uint8_t VSYS_STAT = 0x01;
        };

        struct REG0C
        {
            static const uint8_t _ADDR = 0x0c;

            static const uint8_t WATCHDOG_FAULT = 0x80;
            //Status 0 – Normal 
            //1- Watchdog timer expiration
            static const uint8_t BOOST_FAULT = 0x40;
            //0 – Normal 
            //1 – VBUS overloaded in OTG, or VBUS OVP, or battery is too low in boost mode
            static const uint8_t CHRG_FAULT = 0x30;
            //00 – Normal 
            //01 – Input fault (VBUS > VACOV or VBAT < VBUS < VVBUSMIN(typical 3.8V) )
            //10 - Thermal shutdown
            //11 – Charge Safety Timer Expiration
            static const uint8_t BAT_FAULT = 0x08;
            //0 – Normal
            //1 – BATOVP (VBAT > VBATOVP)
            static const uint8_t NTC_FAULT = 0x07;
            //Buck Mode:
            //000 – Normal 010 – TS Warm 011 – TS Cool 101 – TS Cold 110 – TS Hot
            //Boost Mode:
            //000 – Normal 101 – TS Cold 110 – TS Hot

        };

        struct REG0D
        {
            static const uint8_t _ADDR = 0x0d;

            static const uint8_t FORCE_VINDPM = 0x80;
            static const uint8_t VINDPM = 0x7F;
        };

        struct REG0E
        {
            static const uint8_t _ADDR = 0x0e;
        };

        struct REG0F
        {
            static const uint8_t _ADDR = 0x0f;
        };

        struct REG10
        {
            static const uint8_t _ADDR = 0x10;
        };

        struct REG11
        {
            static const uint8_t _ADDR = 0x11;

            static const uint8_t VBUS_GD = 0x80;
            static const uint8_t VBUSV = 0x7F;
        };

        struct REG12
        {
            static const uint8_t _ADDR = 0x12;
        };

        struct REG13
        {
            static const uint8_t _ADDR = 0x13;

            static const uint8_t VDPM_STAT = 0x80;
            static const uint8_t IDPM_STAT = 0x40;
            static const uint8_t IDPM_LIM = 0x3F;
        };

        struct REG14
        {
            static const uint8_t _ADDR = 0x14;

            static const uint8_t REG_RST = 0x80;
        };
    };

    BQ25896(const PinName sda, const PinName scl):
        i2c(sda, scl),
        I2C_ADDR(BQ25896_I2C_ADDR << 1) {
    }

    /*** REG00 ***/

    //enable high impedance mode (low power)
    uint8_t enableHIZ(){
        uint8_t reg00 = readRegister(REGISTER::REG00::_ADDR);
        setBit(&reg00, REGISTER::REG00::EN_HIZ);
        return setRegister(REGISTER::REG00::_ADDR, reg00);
    }

    //disable high impedance mode (low power)
    uint8_t disableHIZ(){
        uint8_t reg00 = readRegister(REGISTER::REG00::_ADDR);
        unsetBit(&reg00, REGISTER::REG00::EN_HIZ);
        return setRegister(REGISTER::REG00::_ADDR, reg00);
    }

    uint8_t enableILIMPin(){
        uint8_t reg00 = readRegister(REGISTER::REG00::_ADDR);
        setBit(&reg00, REGISTER::REG00::EN_ILIM);
        return setRegister(REGISTER::REG00::_ADDR, reg00);
    }

    uint8_t disableILIMPin(){
        uint8_t reg00 = readRegister(REGISTER::REG00::_ADDR);
        unsetBit(&reg00, REGISTER::REG00::EN_ILIM);
        return setRegister(REGISTER::REG00::_ADDR, reg00);
    }

    uint8_t setMaxILIM(){
        uint8_t reg00 = readRegister(REGISTER::REG00::_ADDR);
        setBit(&reg00, REGISTER::REG00::IINLIM);
        return setRegister(REGISTER::REG00::_ADDR, reg00);
    }

    //set in mA
    uint8_t setIINLIM(int i){
        if (i <= 3250){
            uint8_t reg00 = readRegister(REGISTER::REG00::_ADDR);
            uint8_t mask = (uint8_t) ((i-100) / 50);
            unsetBit(&reg00, REGISTER::REG00::IINLIM);
            setBit(&reg00, mask);
            return setRegister(REGISTER::REG00::_ADDR, reg00);
        } else {
            return 1;
        }
    }

    /*** REG01 ***/

        //Input Voltage Limit Offset in mV
    uint8_t setVINDPM_OS(int val){
        if(val <= 3100){
            uint8_t reg = readRegister(REGISTER::REG01::_ADDR);
            unsetBit(&reg, REGISTER::REG01::VINDPM_OS);
            setBit(&reg, (uint8_t) (val / 100));
            return setRegister(REGISTER::REG01::_ADDR, reg);
        } else {
            return 1;
        }
    }

    /*** REG02 ***/

    uint8_t oneShotADC(){
        uint8_t reg = readRegister(REGISTER::REG02::_ADDR);
        setBit(&reg, REGISTER::REG02::CONV_START);
        return setRegister(REGISTER::REG02::_ADDR, reg);
    }

    uint8_t startADC(){
        uint8_t reg = readRegister(REGISTER::REG02::_ADDR);
        setBit(&reg, REGISTER::REG02::CONV_RATE);
        return setRegister(REGISTER::REG02::_ADDR, reg);
    }

    uint8_t stopADC(){
        uint8_t reg = readRegister(REGISTER::REG02::_ADDR);
        unsetBit(&reg, REGISTER::REG02::CONV_RATE);
        return setRegister(REGISTER::REG02::_ADDR, reg);
    }

    //Force Input Detection
    uint8_t setFORCE_DPDM(){
        uint8_t reg = readRegister(REGISTER::REG02::_ADDR);
        setBit(&reg, REGISTER::REG02::FORCE_DPDM);
        return setRegister(REGISTER::REG02::_ADDR, reg);
    }

    uint8_t unsetFORCE_DPDM(){
        uint8_t reg = readRegister(REGISTER::REG02::_ADDR);
        unsetBit(&reg, REGISTER::REG02::FORCE_DPDM);
        return setRegister(REGISTER::REG02::_ADDR, reg);
    }

    //Automatic Input Detection Enable
    uint8_t enableAUTO_DPDM(){
        uint8_t reg = readRegister(REGISTER::REG02::_ADDR);
        setBit(&reg, REGISTER::REG02::AUTO_DPDM_EN);
        return setRegister(REGISTER::REG02::_ADDR, reg);
    }

    uint8_t disableAUTO_DPDM(){
        uint8_t reg = readRegister(REGISTER::REG02::_ADDR);
        unsetBit(&reg, REGISTER::REG02::AUTO_DPDM_EN);
        return setRegister(REGISTER::REG02::_ADDR, reg);
    }

    /*** REG03 ***/

    //Battery Load enable
    uint8_t enableIBATLOAD(){
        uint8_t reg = readRegister(REGISTER::REG03::_ADDR);
        setBit(&reg, REGISTER::REG03::BAT_LOADEN);
        return setRegister(REGISTER::REG03::_ADDR, reg);
    }

    uint8_t disableIBATLOAD(){
        uint8_t reg = readRegister(REGISTER::REG03::_ADDR);
        unsetBit(&reg, REGISTER::REG03::BAT_LOADEN);
        return setRegister(REGISTER::REG03::_ADDR, reg);
    }

    uint8_t enableOTG(){
        uint8_t reg03 = readRegister(REGISTER::REG03::_ADDR);
        setBit(&reg03, REGISTER::REG03::OTG_CONFIG);
        return setRegister(REGISTER::REG03::_ADDR, reg03);
    }

    uint8_t disableOTG(){
        uint8_t reg03 = readRegister(REGISTER::REG03::_ADDR);
        unsetBit(&reg03, REGISTER::REG03::OTG_CONFIG);
        return setRegister(REGISTER::REG03::_ADDR, reg03);
    }

    bool getOTG(){
        int reg = readRegister(REGISTER::REG03::_ADDR);
        return (bool) (reg & REGISTER::REG03::OTG_CONFIG);
    }

    uint8_t enableCHRG(){
        uint8_t reg03 = readRegister(REGISTER::REG03::_ADDR);
        setBit(&reg03, REGISTER::REG03::CHG_CONFIG);
        return setRegister(REGISTER::REG03::_ADDR, reg03);
    }

    uint8_t disableCHRG(){
        uint8_t reg03 = readRegister(REGISTER::REG03::_ADDR);
        unsetBit(&reg03, REGISTER::REG03::CHG_CONFIG);
        return setRegister(REGISTER::REG03::_ADDR, reg03);
    }

    bool getCHRG(){
        int reg = readRegister(REGISTER::REG03::_ADDR);
        return (bool) (reg & REGISTER::REG03::CHG_CONFIG);
    }

    /*** REG04 ***/

    //Current pulse control Enable
    uint8_t enablePUMPX(){
        uint8_t reg = readRegister(REGISTER::REG04::_ADDR);
        setBit(&reg, REGISTER::REG04::EN_PUMPX);
        return setRegister(REGISTER::REG04::_ADDR, reg);
    }

    uint8_t disablePUMPX(){
        uint8_t reg = readRegister(REGISTER::REG04::_ADDR);
        unsetBit(&reg, REGISTER::REG04::EN_PUMPX);
        return setRegister(REGISTER::REG04::_ADDR, reg);
    }

    //Fast Charge Current Limit in mA
    uint8_t setICHG(int val){
        if(val <= 3008){
            uint8_t reg = readRegister(REGISTER::REG04::_ADDR);
            unsetBit(&reg, REGISTER::REG04::ICHG);
            setBit(&reg, (uint8_t) (val / 64));
            return setRegister(REGISTER::REG04::_ADDR, reg);
        } else {
            return 1;
        }
    }

    //charging current limit in mA
    int getICHG(){
        return (readRegister(REGISTER::REG04::_ADDR) & REGISTER::REG04::ICHG) * 64;
    }

    /*** REG05 ***/

    //Precharge Current Limit in mA
    uint8_t setIPRECHG(int val){
        if(val <= 1024){
            uint8_t reg = readRegister(REGISTER::REG05::_ADDR);
            unsetBit(&reg, REGISTER::REG05::IPRECHG);
            setBit(&reg, (uint8_t) ((val - 64) / 64) << 4);
            return setRegister(REGISTER::REG05::_ADDR, reg);
        } else {
            return 1;
        }
    }  

    //Termination Current Limit
    uint8_t setITERM(int val){
        if(val <= 1024){
            uint8_t reg = readRegister(REGISTER::REG05::_ADDR);
            unsetBit(&reg, REGISTER::REG05::ITERM);
            setBit(&reg, (uint8_t) ((val - 64) / 64));
            return setRegister(REGISTER::REG05::_ADDR, reg);
        } else {
            return 1;
        }
    }  

    /*** REG06 ***/

    //Charge Voltage Limit in mV
    uint8_t setVREG(int val){
        if(val >= 3840 && val <= 4608){
            uint8_t reg = readRegister(REGISTER::REG06::_ADDR);
            unsetBit(&reg, REGISTER::REG06::VREG);
            setBit(&reg, (uint8_t) (((val - 3640) / 16)<<2));
            return setRegister(REGISTER::REG06::_ADDR, reg);
        } else {
            return 1;
        }
    }

    /*** REG07 ***/

    uint8_t disableWATCHDOG(){
        uint8_t reg = readRegister(REGISTER::REG07::_ADDR);
        unsetBit(&reg, REGISTER::REG07::WATCHDOG);
        return setRegister(REGISTER::REG07::_ADDR, reg);
    }

    uint8_t WATCHDOG40s(){
        uint8_t reg = readRegister(REGISTER::REG07::_ADDR);
        unsetBit(&reg, REGISTER::REG07::WATCHDOG);
        setBit(&reg, 0x01 << 4);
        return setRegister(REGISTER::REG07::_ADDR, reg);
    }

    uint8_t WATCHDOG80s(){
        uint8_t reg = readRegister(REGISTER::REG07::_ADDR);
        unsetBit(&reg, REGISTER::REG07::WATCHDOG);
        setBit(&reg, 0x02 << 4);
        return setRegister(REGISTER::REG07::_ADDR, reg);
    }

    uint8_t WATCHDOG160s(){
        uint8_t reg = readRegister(REGISTER::REG07::_ADDR);
        unsetBit(&reg, REGISTER::REG07::WATCHDOG);
        setBit(&reg, 0x03 << 4);
        return setRegister(REGISTER::REG07::_ADDR, reg);
    }

    /*** REG0A ***/

    //Boost Mode Voltage Regulation in mV
    uint8_t setBOOSTV(int val){
        if(val >= 4550 && val <= 5510){
            uint8_t reg = readRegister(REGISTER::REG0A::_ADDR);
            unsetBit(&reg, REGISTER::REG0A::BOOSTV);
            setBit(&reg, (uint8_t) (((val - 4550) / 64)<<4));
            return setRegister(REGISTER::REG0A::_ADDR, reg);
        } else {
            return 1;
        }
    }

    //Boost Mode Current Limit
    uint8_t setBOOST_LIM(int val){
        if(val <= 6){
            uint8_t reg = readRegister(REGISTER::REG0A::_ADDR);
            unsetBit(&reg, REGISTER::REG0A::BOOST_LIM);
            setBit(&reg, (uint8_t) val);
            return setRegister(REGISTER::REG0A::_ADDR, reg);
        } else {
            return 1;
        }
    }

    /*** REG0B ***/

    int getVBUS_STAT(){
        uint8_t reg = readRegister(REGISTER::REG0B::_ADDR);
        return (reg & REGISTER::REG0B::VBUS_STAT) >> 5;
    }

    int getCHRG_STAT(){
        uint8_t reg = readRegister(REGISTER::REG0B::_ADDR);
        return (reg & REGISTER::REG0B::CHRG_STAT) >> 3;
    }

    int getPG_STAT(){
        uint8_t reg = readRegister(REGISTER::REG0B::_ADDR);
        return (reg & REGISTER::REG0B::PG_STAT) >> 2;
    }

    int getVSYS_STAT(){
        uint8_t reg = readRegister(REGISTER::REG0B::_ADDR);
        return reg & REGISTER::REG0B::VSYS_STAT;
    }

    /*** REG0C ***/

    int getFAULT(){
        return readRegister(REGISTER::REG0C::_ADDR);
    }

    int getWATCHDOG_FAULT(){
        return getFAULT() & REGISTER::REG0C::WATCHDOG_FAULT >> 7;
    }

    int getBOOST_FAULT(){
        return getFAULT() & REGISTER::REG0C::BOOST_FAULT >> 6;
    }

    int getBAT_FAULT(){
        return getFAULT() & REGISTER::REG0C::BAT_FAULT >> 3;
    }

    int getCHRG_FAULT(){
        return getFAULT() & REGISTER::REG0C::CHRG_FAULT >> 4;
    }

    int getNTC_FAULT(){
        return getFAULT() & REGISTER::REG0C::NTC_FAULT;
    }

    /*** REG0D ***/

    //VINDPM Threshold Setting Method absolute
    uint8_t enableFORCE_VINDPM(){
        uint8_t reg = readRegister(REGISTER::REG0D::_ADDR);
        setBit(&reg, REGISTER::REG0D::FORCE_VINDPM);
        return setRegister(REGISTER::REG0D::_ADDR, reg);
    }

    uint8_t disableFORCE_VINDPM(){
        uint8_t reg = readRegister(REGISTER::REG0D::_ADDR);
        unsetBit(&reg, REGISTER::REG0D::FORCE_VINDPM);
        return setRegister(REGISTER::REG0D::_ADDR, reg);
    }

    //Absolute VINDPM Threshold in mV
    uint8_t setVINDPM(int val){
        if(val >= 3900 && val <= 15300){
            uint8_t reg = readRegister(REGISTER::REG0D::_ADDR);
            unsetBit(&reg, REGISTER::REG0D::VINDPM);
            setBit(&reg, (uint8_t) ((val - 2600) / 100));
            return setRegister(REGISTER::REG0D::_ADDR, reg);
        } else {
            return 1;
        }
    }

    int getVINDPM(){
        uint8_t reg = readRegister(REGISTER::REG0D::_ADDR);
        return (int) ((reg & REGISTER::REG0D::VINDPM) * 100) + 2600;
    }

    /*** REG0E ***/

    //ADC conversion of Battery Voltage (VBAT)
    int getBATV(){
        return ((int) ((readRegister(REGISTER::REG0E::_ADDR) & 0x7F))) * 20 + 2304;
    }

    /*** REG0F ***/

    //ADDC conversion of System Voltage (VSYS)
    int getSYSV(){
        return ((int) readRegister(REGISTER::REG0F::_ADDR)) * 20 + 2304;
    }

    /*** REG10 ***/

    //REGN in percentage
    float getTSPCT(){
        return ((float) readRegister(REGISTER::REG10::_ADDR)) * 0.465 + 21;
    }

    /*** REG11 ***/

    //connected input Voltage in V .. -1 if no connection
    float getVBUSV(){
        uint8_t reg = readRegister(REGISTER::REG11::_ADDR);
        // if (reg & REGISTER::REG11::VBUS_GD){
            return (float) (reg & REGISTER::REG11::VBUSV) * 0.1 + 2.6;
        // } else {
        //     return -1.0;
        // }
    }

    int getVBUS_GD(){
        return readRegister(REGISTER::REG11::_ADDR) & REGISTER::REG11::VBUS_GD >> 7;
    }

    /*** REG12 ***/

    //charging current in mA
    int getICHGR(){
        return ((int) readRegister(REGISTER::REG12::_ADDR)) * 50;
    }

    /*** REG13 ***/

    int getVDPM_STAT(){
        return readRegister(REGISTER::REG13::_ADDR) & REGISTER::REG13::VDPM_STAT >> 7;
    }

    int getIDPM_STAT(){
        return readRegister(REGISTER::REG13::_ADDR) & REGISTER::REG13::IDPM_STAT >> 6;
    }

    int getIDPM_LIM(){
        return (int)(readRegister(REGISTER::REG13::_ADDR) & REGISTER::REG13::IDPM_LIM) * 50 + 100;
    }

    /*** REG14 ***/

    int reset(){
        uint8_t reg = readRegister(REGISTER::REG14::_ADDR);
        setBit(&reg, REGISTER::REG14::REG_RST);
        return setRegister(REGISTER::REG14::_ADDR, reg);
    }

    /*** REG END ***/
    
    int setRegister(const uint8_t reg, const uint8_t value) {
        char cmd[2] = { reg, value };
        return i2c.write( (int) I2C_ADDR, cmd, 2);
    }

    int readRegister(const uint8_t reg){
        uint8_t result;
        i2c.write( (int) I2C_ADDR, (const char *) &reg, 1 );
        i2c.read( (int) I2C_ADDR, (char *) &result, 1 );
        return result;
    }

    void setBit(uint8_t *reg, uint8_t mask){
        *reg |= mask;
    }

    void unsetBit(uint8_t *reg, uint8_t mask){
        *reg &= ~mask;
    }

    protected:
    uint8_t I2C_ADDR;
    I2C i2c;
};

#endif /*__BQ25896_H__*/