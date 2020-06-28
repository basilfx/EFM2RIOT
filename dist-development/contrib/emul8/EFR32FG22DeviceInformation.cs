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
    public class EFR32FG22DeviceInformation: IDoubleWordPeripheral, IKnownSize
    {
        public EFR32FG22DeviceInformation(ushort deviceNumber, ushort flashSize, ushort sramSize, byte productRevision = 0)
        {
            this.flashSize = flashSize;
            this.sramSize = sramSize;
            this.productRevision = productRevision;
            this.deviceFamily = 0x0;
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
                return 0x2d8;
            }
        }

        public ulong EUI { get; set; }
        public ulong Unique { get; set; }

        private readonly ushort flashSize;
        private readonly ushort sramSize;
        private readonly byte productRevision;
        private readonly byte deviceFamily;
        private readonly ushort deviceNumber;

        // This structure should resemble the structure of efr32fg22_devinfo.h.
        private enum DeviceInformationOffset : long
        {
            PART             = 0x000, // Part Info                                         
            MEMINFO          = 0x004, // Memory Info                                       
            MSIZE            = 0x008, // Memory Size                                       
            PKGINFO          = 0x00c, // Misc Device Info                                  
            CUSTOMINFO       = 0x010, // Custom Part Info                                  
            SWFIX            = 0x014, // SW Fix Register                                   
            SWCAPA0          = 0x018, // Software Restriction                              
            SWCAPA1          = 0x01c, // Software Restriction                              
            EXTINFO          = 0x024, // External Component Info                           
            EUI48L           = 0x03c, // EUI 48 Low                                        
            EUI48H           = 0x040, // EUI 48 High                                       
            EUI64L           = 0x044, // EUI64 Low                                         
            EUI64H           = 0x048, // EUI64 High                                        
            CALTEMP          = 0x04c, // Calibration temperature Information               
            EMUTEMP          = 0x050, // EMU Temperature Sensor Calibration Information    
            HFRCODPLLCAL[18U] = 0x054, //                                                   
            HFRCOEM23CAL[18U] = 0x058, //                                                   
            HFRCOSECAL[18U]  = 0x05c, //                                                   
            MODULENAME0      = 0x060, // Module Name Information                           
            MODULENAME1      = 0x064, // Module Name Information                           
            MODULENAME2      = 0x068, // Module Name Information                           
            MODULENAME3      = 0x06c, // Module Name Information                           
            MODULENAME4      = 0x070, // Module Name Information                           
            MODULENAME5      = 0x074, // Module Name Information                           
            MODULENAME6      = 0x078, // Module Name Information                           
            MODULEINFO       = 0x07c, // Module Information                                
            MODXOCAL         = 0x080, // Module External Oscillator Calibration Information
            IADC0GAIN0       = 0x0b0, // IADC Gain Calibration                             
            IADC0GAIN1       = 0x0b4, // IADC Gain Calibration                             
            IADC0OFFSETCAL0  = 0x0b8, // IADC Offset Calibration                           
            IADC0NORMALOFFSETCAL0 = 0x0bc, // IADC Offset Calibration                           
            IADC0NORMALOFFSETCAL1 = 0x0c0, // IADC Offset Calibration                           
            IADC0HISPDOFFSETCAL0 = 0x0c4, // IADC Offset Calibration                           
            IADC0HISPDOFFSETCAL1 = 0x0c8, // IADC Offset Calibration                           
            LEGACY           = 0x12c, // Legacy Device Info                                
            RTHERM           = 0x18c, // Thermistor Calibration                            
        }
    }
}
