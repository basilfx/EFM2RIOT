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
    public class EFM32GG11BDeviceInformation: IDoubleWordPeripheral, IKnownSize
    {
        public EFM32GG11BDeviceInformation(ushort deviceNumber, ushort flashSize, ushort sramSize, byte productRevision = 0)
        {
            this.flashSize = flashSize;
            this.sramSize = sramSize;
            this.productRevision = productRevision;
            this.deviceFamily = 0x64;
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
                return 0x2b4;
            }
        }

        public ulong EUI { get; set; }
        public ulong Unique { get; set; }

        private readonly ushort flashSize;
        private readonly ushort sramSize;
        private readonly byte productRevision;
        private readonly byte deviceFamily;
        private readonly ushort deviceNumber;

        // This structure should resemble the structure of efm32gg11b_devinfo.h.
        private enum DeviceInformationOffset : long
        {
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
            ADC1CAL0         = 0x06c, // ADC1 calibration register 0 
            ADC1CAL1         = 0x070, // ADC1 calibration register 1 
            ADC1CAL2         = 0x074, // ADC1 calibration register 2 
            ADC1CAL3         = 0x078, // ADC1 calibration register 3 
            HFRCOCAL0        = 0x07c, // HFRCO Calibration Register (4 MHz) 
            HFRCOCAL3        = 0x088, // HFRCO Calibration Register (7 MHz) 
            HFRCOCAL6        = 0x094, // HFRCO Calibration Register (13 MHz) 
            HFRCOCAL7        = 0x098, // HFRCO Calibration Register (16 MHz) 
            HFRCOCAL8        = 0x09c, // HFRCO Calibration Register (19 MHz) 
            HFRCOCAL10       = 0x0a4, // HFRCO Calibration Register (26 MHz) 
            HFRCOCAL11       = 0x0a8, // HFRCO Calibration Register (32 MHz) 
            HFRCOCAL12       = 0x0ac, // HFRCO Calibration Register (38 MHz) 
            HFRCOCAL13       = 0x0b0, // HFRCO Calibration Register (48 MHz) 
            HFRCOCAL14       = 0x0b4, // HFRCO Calibration Register (56 MHz) 
            HFRCOCAL15       = 0x0b8, // HFRCO Calibration Register (64 MHz) 
            HFRCOCAL16       = 0x0bc, // HFRCO Calibration Register (72 MHz) 
            AUXHFRCOCAL0     = 0x0dc, // AUXHFRCO Calibration Register (4 MHz) 
            AUXHFRCOCAL3     = 0x0e8, // AUXHFRCO Calibration Register (7 MHz) 
            AUXHFRCOCAL6     = 0x0f4, // AUXHFRCO Calibration Register (13 MHz) 
            AUXHFRCOCAL7     = 0x0f8, // AUXHFRCO Calibration Register (16 MHz) 
            AUXHFRCOCAL8     = 0x0fc, // AUXHFRCO Calibration Register (19 MHz) 
            AUXHFRCOCAL10    = 0x104, // AUXHFRCO Calibration Register (26 MHz) 
            AUXHFRCOCAL11    = 0x108, // AUXHFRCO Calibration Register (32 MHz) 
            AUXHFRCOCAL12    = 0x10c, // AUXHFRCO Calibration Register (38 MHz) 
            AUXHFRCOCAL13    = 0x110, // AUXHFRCO Calibration Register (48 MHz) 
            AUXHFRCOCAL14    = 0x114, // AUXHFRCO Calibration Register (50 MHz) 
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
            VDAC0MAINCAL     = 0x180, // VDAC0 Cals for Main Path 
            VDAC0ALTCAL      = 0x184, // VDAC0 Cals for Alternate Path 
            VDAC0CH1CAL      = 0x188, // VDAC0 CH1 Error Cal 
            OPA0CAL0         = 0x18c, // OPA0 Calibration Register for DRIVESTRENGTH 0, INCBW=1 
            OPA0CAL1         = 0x190, // OPA0 Calibration Register for DRIVESTRENGTH 1, INCBW=1 
            OPA0CAL2         = 0x194, // OPA0 Calibration Register for DRIVESTRENGTH 2, INCBW=1 
            OPA0CAL3         = 0x198, // OPA0 Calibration Register for DRIVESTRENGTH 3, INCBW=1 
            OPA0CAL4         = 0x19c, // OPA0 Calibration Register for DRIVESTRENGTH 0, INCBW=0 
            OPA0CAL5         = 0x1a0, // OPA0 Calibration Register for DRIVESTRENGTH 1, INCBW=0 
            OPA0CAL6         = 0x1a4, // OPA0 Calibration Register for DRIVESTRENGTH 2, INCBW=0 
            OPA0CAL7         = 0x1a8, // OPA0 Calibration Register for DRIVESTRENGTH 3, INCBW=0 
            OPA1CAL0         = 0x1ac, // OPA1 Calibration Register for DRIVESTRENGTH 0, INCBW=1 
            OPA1CAL1         = 0x1b0, // OPA1 Calibration Register for DRIVESTRENGTH 1, INCBW=1 
            OPA1CAL2         = 0x1b4, // OPA1 Calibration Register for DRIVESTRENGTH 2, INCBW=1 
            OPA1CAL3         = 0x1b8, // OPA1 Calibration Register for DRIVESTRENGTH 3, INCBW=1 
            OPA1CAL4         = 0x1bc, // OPA1 Calibration Register for DRIVESTRENGTH 0, INCBW=0 
            OPA1CAL5         = 0x1c0, // OPA1 Calibration Register for DRIVESTRENGTH 1, INCBW=0 
            OPA1CAL6         = 0x1c4, // OPA1 Calibration Register for DRIVESTRENGTH 2, INCBW=0 
            OPA1CAL7         = 0x1c8, // OPA1 Calibration Register for DRIVESTRENGTH 3, INCBW=0 
            OPA2CAL0         = 0x1cc, // OPA2 Calibration Register for DRIVESTRENGTH 0, INCBW=1 
            OPA2CAL1         = 0x1d0, // OPA2 Calibration Register for DRIVESTRENGTH 1, INCBW=1 
            OPA2CAL2         = 0x1d4, // OPA2 Calibration Register for DRIVESTRENGTH 2, INCBW=1 
            OPA2CAL3         = 0x1d8, // OPA2 Calibration Register for DRIVESTRENGTH 3, INCBW=1 
            OPA2CAL4         = 0x1dc, // OPA2 Calibration Register for DRIVESTRENGTH 0, INCBW=0 
            OPA2CAL5         = 0x1e0, // OPA2 Calibration Register for DRIVESTRENGTH 1, INCBW=0 
            OPA2CAL6         = 0x1e4, // OPA2 Calibration Register for DRIVESTRENGTH 2, INCBW=0 
            OPA2CAL7         = 0x1e8, // OPA2 Calibration Register for DRIVESTRENGTH 3, INCBW=0 
            OPA3CAL0         = 0x1ec, // OPA3 Calibration Register for DRIVESTRENGTH 0, INCBW=1 
            OPA3CAL1         = 0x1f0, // OPA3 Calibration Register for DRIVESTRENGTH 1, INCBW=1 
            OPA3CAL2         = 0x1f4, // OPA3 Calibration Register for DRIVESTRENGTH 2, INCBW=1 
            OPA3CAL3         = 0x1f8, // OPA3 Calibration Register for DRIVESTRENGTH 3, INCBW=1 
            OPA3CAL4         = 0x1fc, // OPA3 Calibration Register for DRIVESTRENGTH 0, INCBW=0 
            OPA3CAL5         = 0x200, // OPA3 Calibration Register for DRIVESTRENGTH 1, INCBW=0 
            OPA3CAL6         = 0x204, // OPA3 Calibration Register for DRIVESTRENGTH 2, INCBW=0 
            OPA3CAL7         = 0x208, // OPA3 Calibration Register for DRIVESTRENGTH 3, INCBW=0 
            CSENGAINCAL      = 0x20c, // Cap Sense Gain Adjustment 
            USHFRCOCAL7      = 0x268, // USHFRCO Calibration Register (16 MHz) 
            USHFRCOCAL11     = 0x278, // USHFRCO Calibration Register (32 MHz) 
            USHFRCOCAL13     = 0x280, // USHFRCO Calibration Register (48 MHz) 
            USHFRCOCAL14     = 0x284, // USHFRCO Calibration Register (50 MHz) 
            CURRMON5V        = 0x2ac, // 5V Current monitor Transconductance 
        }
    }
}
