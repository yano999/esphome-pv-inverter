#pragma once

namespace helpers {

    
    float combine_modbus_registers(float low_value, float high_value) {
        
        if (isnan(low_value) || isnan(high_value)) {
            return NAN;
        }

        uint32_t low = (uint32_t)low_value;
        uint32_t high = (uint32_t)high_value;

        uint32_t combined_value = (high << 16) | (low & 0xFFFF);

        if (combined_value > 0x7FFFFFFF) {
            return (float)((int32_t)combined_value);
        }

        return (float)combined_value;
    }

}