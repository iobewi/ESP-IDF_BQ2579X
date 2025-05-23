#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace bq2579x
{
// REG19h - ICO Current Limit (Read Only)
class ICO_Current_Limit_Register {
public:
    static constexpr uint8_t reg_addr = 0x19;

    uint16_t get_value() const {
        return raw_ * 10; // step size = 10 mA
    }

    void set_raw(uint16_t raw) { raw_ = raw & 0x01FF; }
    uint16_t get_raw() const { return raw_; }

private:
    uint16_t raw_ = 0;
};

// REG31h - IBUS_ADC Register
class IBUS_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x31;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne le courant en mA (signé) basé sur un offset fixe à 0 et un pas de 1 mA
    uint16_t get_value() const {
        return static_cast<uint16_t>(raw_);
    }

private:
    uint16_t raw_ = 0;
};

// REG33h - IBAT_ADC Register
class IBAT_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x33;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne le courant batterie en mA (signé)
    int16_t get_value() const {
        return static_cast<int16_t>(raw_);
    }

private:
    uint16_t raw_ = 0;
};

// REG35h - VBUS_ADC Register
class VBUS_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x35;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la tension VBUS en millivolts
    uint16_t get_value() const {
        return raw_; // LSB = 1mV
    }

private:
    uint16_t raw_ = 0;
};

// REG37h - VAC1_ADC Register
class VAC1_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x37;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la tension VAC1 en millivolts
    uint16_t get_value() const {
        return raw_; // LSB = 1mV
    }

private:
    uint16_t raw_ = 0;
};

// REG39h - VAC2_ADC Register
class VAC2_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x39;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la tension VAC2 en millivolts
    uint16_t get_value() const {
        return raw_; // LSB = 1mV
    }

private:
    uint16_t raw_ = 0;
};

// REG3Bh - VBAT_ADC Register
class VBAT_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x3B;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la tension VBAT en millivolts
    uint16_t get_value() const {
        return raw_; // LSB = 1mV
    }

private:
    uint16_t raw_ = 0;
};

// REG3Dh - VSYS_ADC Register
class VSYS_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x3D;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la tension VSYS en millivolts
    uint16_t get_value() const {
        return raw_; // LSB = 1mV
    }

private:
    uint16_t raw_ = 0;
};

// REG3Fh - TS_ADC Register
class TS_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x3F;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la valeur en millièmes de pourcent (par exemple : 12345 => 12.345 %)
    uint32_t get_value() const {
        // 1 LSB = 0.0976563 %
        // 0.0976563 * 1000 ≈ 97.6563 milli-%
        // Utilisation d'un facteur entier (97.65625 ≈ 250 / 256)
        return (static_cast<uint32_t>(raw_) * 250) / 256;
    }

private:
    uint16_t raw_ = 0;
};

// REG41h - TDIE_ADC Register
class TDIE_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x41;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la température en dixièmes de degrés Celsius (par exemple : 253 => 25.3°C)
    int16_t get_value() const {
        int16_t signed_val = static_cast<int16_t>(raw_);
        return signed_val * 5; // 0.5°C * 10 = 5 dixièmes
    }

private:
    uint16_t raw_ = 0;
};

// REG43h - D+_ADC Register
class DPlus_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x43;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la tension D+ en millivolts (entier)
    uint16_t get_value() const {
        return raw_; // LSB = 1 mV
    }

private:
    uint16_t raw_ = 0;
};

// REG45h - D-_ADC Register
class DMinus_ADC_Register {
public:
    static constexpr uint8_t reg_addr = 0x45;

    void set_raw(uint16_t raw) { raw_ = raw; }
    uint16_t get_raw() const { return raw_; }

    // Retourne la tension D- en millivolts (entier uniquement)
    uint16_t get_value() const {
        return raw_; // LSB = 1 mV
    }

private:
    uint16_t raw_ = 0;
};

// REG48h - Part Information Register
class Part_Information_Register {
public:
    static constexpr uint8_t reg_addr = 0x48;

    struct Values {
        uint8_t part_number;     // Bits 5:3
        uint8_t device_revision; // Bits 2:0
    };

    void set_raw(uint8_t raw) { raw_ = raw; }
    uint8_t get_raw() const { return raw_; }

    Values get_values() const {
        Values v;
        v.part_number = (raw_ >> 3) & 0x07;
        v.device_revision = raw_ & 0x07;
        return v;
    }

private:
    uint8_t raw_ = 0;
};


}