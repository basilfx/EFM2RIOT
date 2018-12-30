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
    public class EFR32MG1PDeviceInformation: IDoubleWordPeripheral, IKnownSize
    {
        public EFR32MG1PDeviceInformation(ushort deviceNumber, ushort flashSize, ushort sramSize, byte productRevision = 0)
        {
            this.flashSize = flashSize;
            this.sramSize = sramSize;
            this.productRevision = productRevision;
            this.deviceFamily = 0x10;
            this.deviceNumber = deviceNumber;
        }

        public void Reset()
        {
        }

        public uint ReadDoubleWord(long offset)
        {
            switch((DeviceInformationOffset)offset)
            {
            case DeviceInformationOffset.EUI48L:
                return (uint)(EUI >> 32);
            case DeviceInformationOffset.EUI48H:
                return (uint)(EUI & 0xFFFFFFFF);
            case DeviceInformationOffset.UNIQUEL:
                return (uint)(Unique >> 32);
            case DeviceInformationOffset.UNIQUEH:
                return (uint)(Unique & 0xFFFFFFFF);
            case DeviceInformationOffset.MSIZE:
                return (uint)((sramSize << 16) | (flashSize & 0xFFFF));
            case DeviceInformationOffset.PART:
                return (uint)((productRevision << 24) | ((byte)deviceFamily << 16) | deviceNumber);
            case DeviceInformationOffset.DEVINFOREV:
                return 0xFFFFFF00 | 0x01;
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
                return 0x184;
            }
        }

        public ulong EUI { get; set; }
        public ulong Unique { get; set; }

        private readonly ushort flashSize;
        private readonly ushort sramSize;
        private readonly byte productRevision;
        private readonly byte deviceFamily;
        private readonly ushort deviceNumber;

        // This structure should resemble the structure of efr32mg1p_devinfo.h.
        private enum DeviceInformationOffset : long
        {
            MODULEINFO       = 0x000, // Module trace information 
            MODXOCAL         = 0x004, // Module Crystal Oscillator Calibration 
            EXTINFO          = 0x01c, // External Component description 
            EUI48L           = 0x024, // EUI48 OUI and Unique identifier 
            EUI48H           = 0x028, // OUI 
            CUSTOMINFO       = 0x02c, // Custom information 
            MEMINFO          = 0x030, // Flash page size and misc. chip information 
            UNIQUEL          = 0x03c, // Low 32 bits of device unique number 
            UNIQUEH          = 0x040, // High 32 bits of device unique number 
            MSIZE            = 0x044, // Flash and SRAM Memory size in kB 
            PART             = 0x048, // Part description 
            DEVINFOREV       = 0x04c, // Device information page revision 
            EMUTEMP          = 0x050, // EMU Temperature Calibration Information 
            ADC0CAL0         = 0x05c, // ADC0 calibration register 0 
            ADC0CAL1         = 0x060, // ADC0 calibration register 1 
            ADC0CAL2         = 0x064, // ADC0 calibration register 2 
            ADC0CAL3         = 0x068, // ADC0 calibration register 3 
            HFRCOCAL0        = 0x07c, // HFRCO Calibration Register (4 MHz) 
            HFRCOCAL3        = 0x088, // HFRCO Calibration Register (7 MHz) 
            HFRCOCAL6        = 0x094, // HFRCO Calibration Register (13 MHz) 
            HFRCOCAL7        = 0x098, // HFRCO Calibration Register (16 MHz) 
            HFRCOCAL8        = 0x09c, // HFRCO Calibration Register (19 MHz) 
            HFRCOCAL10       = 0x0a4, // HFRCO Calibration Register (26 MHz) 
            HFRCOCAL11       = 0x0a8, // HFRCO Calibration Register (32 MHz) 
            HFRCOCAL12       = 0x0ac, // HFRCO Calibration Register (38 MHz) 
            AUXHFRCOCAL0     = 0x0dc, // AUXHFRCO Calibration Register (4 MHz) 
            AUXHFRCOCAL3     = 0x0e8, // AUXHFRCO Calibration Register (7 MHz) 
            AUXHFRCOCAL6     = 0x0f4, // AUXHFRCO Calibration Register (13 MHz) 
            AUXHFRCOCAL7     = 0x0f8, // AUXHFRCO Calibration Register (16 MHz) 
            AUXHFRCOCAL8     = 0x0fc, // AUXHFRCO Calibration Register (19 MHz) 
            AUXHFRCOCAL10    = 0x104, // AUXHFRCO Calibration Register (26 MHz) 
            AUXHFRCOCAL11    = 0x108, // AUXHFRCO Calibration Register (32 MHz) 
            AUXHFRCOCAL12    = 0x10c, // AUXHFRCO Calibration Register (38 MHz) 
            VMONCAL0         = 0x13c, // VMON Calibration Register 0 
            VMONCAL1         = 0x140, // VMON Calibration Register 1 
            VMONCAL2         = 0x144, // VMON Calibration Register 2 
            IDAC0CAL0        = 0x154, // IDAC0 Calibration Register 0 
            IDAC0CAL1        = 0x158, // IDAC0 Calibration Register 1 
            DCDCLNVCTRL0     = 0x164, // DCDC Low-noise VREF Trim Register 0 
            DCDCLPVCTRL0     = 0x168, // DCDC Low-power VREF Trim Register 0 
            DCDCLPVCTRL1     = 0x16c, // DCDC Low-power VREF Trim Register 1 
            DCDCLPVCTRL2     = 0x170, // DCDC Low-power VREF Trim Register 2 
            DCDCLPVCTRL3     = 0x174, // DCDC Low-power VREF Trim Register 3 
            DCDCLPCMPHYSSEL0 = 0x178, // DCDC LPCMPHYSSEL Trim Register 0 
            DCDCLPCMPHYSSEL1 = 0x17c, // DCDC LPCMPHYSSEL Trim Register 1 
        }
    }
}
