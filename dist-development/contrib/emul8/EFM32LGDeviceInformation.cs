//
// Copyright (c) Antmicro
// Copyright (c) Bas Stottelaar <basstottelaar@gmail.com>
//
// This file is part of the Emul8 project.
// Full license details are defined in the 'LICENSE' file.
//
using Emul8.Logging;
using Emul8.Peripherals.Bus;

namespace Emul8.Peripherals
{
    [AllowedTranslations(AllowedTranslation.ByteToDoubleWord)]
    public class EFM32LGDeviceInformation: IDoubleWordPeripheral, IKnownSize
    {
        public EFM32LGDeviceInformation(ushort deviceNumber, ushort flashSize, ushort sramSize, byte productRevision = 0)
        {
            this.flashSize = flashSize;
            this.sramSize = sramSize;
            this.productRevision = productRevision;
            this.deviceFamily = 0x4a;
            this.deviceNumber = deviceNumber;
        }

        public void Reset()
        {
        }

        public uint ReadDoubleWord(long offset)
        {
            switch((DeviceInformationOffset)offset)
            {
            case DeviceInformationOffset.UNIQUEL:
                return (uint)(Unique >> 32);
            case DeviceInformationOffset.UNIQUEH:
                return (uint)(Unique & 0xFFFFFFFF);
            case DeviceInformationOffset.MSIZE:
                return (uint)((sramSize << 16) | (flashSize & 0xFFFF));
            case DeviceInformationOffset.PART:
                return (uint)((productRevision << 24) | ((byte)deviceFamily << 16) | deviceNumber);
            default:
                this.LogUnhandledRead(offset);
                return 0;
            }
        }

        public void WriteDoubleWord(long offset, uint value)
        {
            this.LogUnhandledWrite(offset, value);
        }

        public long Size
        {
            get
            {
                return 0x50;
            }
        }

        public ulong Unique { get; set; }

        private readonly ushort flashSize;
        private readonly ushort sramSize;
        private readonly byte productRevision;
        private readonly byte deviceFamily;
        private readonly ushort deviceNumber;

        // This structure should resemble the structure of efm32lg_devinfo.h.
        private enum DeviceInformationOffset : long
        {
            ADC0CAL0         = 0x000, // ADC0 Calibration register 0
            ADC0CAL1         = 0x004, // ADC0 Calibration register 1
            ADC0CAL2         = 0x008, // ADC0 Calibration register 2
            DAC0CAL0         = 0x014, // DAC calibrartion register 0
            DAC0CAL1         = 0x018, // DAC calibrartion register 1
            DAC0CAL2         = 0x01c, // DAC calibrartion register 2
            AUXHFRCOCAL0     = 0x020, // AUXHFRCO calibration register 0
            AUXHFRCOCAL1     = 0x024, // AUXHFRCO calibration register 1
            HFRCOCAL0        = 0x028, // HFRCO calibration register 0
            HFRCOCAL1        = 0x02c, // HFRCO calibration register 1
            MEMINFO          = 0x030, // Memory information
            UNIQUEL          = 0x03c, // Low 32 bits of device unique number
            UNIQUEH          = 0x040, // High 32 bits of device unique number
            MSIZE            = 0x044, // Flash and SRAM Memory size in KiloBytes
            PART             = 0x048, // Part description
        }
    }
}
