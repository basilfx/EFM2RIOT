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
    public class EZR32HGDeviceInformation: IDoubleWordPeripheral, IKnownSize
    {
        public EZR32HGDeviceInformation(ushort deviceNumber, ushort flashSize, ushort sramSize, byte productRevision = 0)
        {
            this.flashSize = flashSize;
            this.sramSize = sramSize;
            this.productRevision = productRevision;
            this.deviceFamily = 0x7a;
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
                return 0x58;
            }
        }

        public ulong Unique { get; set; }

        private readonly ushort flashSize;
        private readonly ushort sramSize;
        private readonly byte productRevision;
        private readonly byte deviceFamily;
        private readonly ushort deviceNumber;

        // This structure should resemble the structure of ezr32hg_devinfo.h.
        private enum DeviceInformationOffset : long
        {
            RADIO1           = 0x000, // Radio information 1
            CAL              = 0x004, // Calibration temperature and checksum
            ADC0CAL0         = 0x008, // ADC0 Calibration register 0
            ADC0CAL1         = 0x00c, // ADC0 Calibration register 1
            ADC0CAL2         = 0x010, // ADC0 Calibration register 2
            IDAC0CAL0        = 0x01c, // IDAC0 calibration register
            USHFRCOCAL0      = 0x020, // USHFRCO calibration register
            AUXHFRCOCAL0     = 0x028, // AUXHFRCO calibration register 0
            AUXHFRCOCAL1     = 0x02c, // AUXHFRCO calibration register 1
            HFRCOCAL0        = 0x030, // HFRCO calibration register 0
            HFRCOCAL1        = 0x034, // HFRCO calibration register 1
            MEMINFO          = 0x038, // Memory information
            RADIO2           = 0x040, // Radio information 2
            UNIQUEL          = 0x044, // Low 32 bits of device unique number
            UNIQUEH          = 0x048, // High 32 bits of device unique number
            MSIZE            = 0x04c, // Flash and SRAM Memory size in KiloBytes
            PART             = 0x050, // Part description
        }
    }
}
