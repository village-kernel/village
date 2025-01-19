//###########################################################################
// vk_drv_usb.cpp
// Hardware Layer class that manage usb
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_usb.h"


/// @brief Contructor
Usb::Usb()
	:base(NULL),
	device(NULL),
	pcgcctl(NULL)
{
}


/// @brief Initialize
void Usb::Initialize()
{
	//Enable usb otg clock
	RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;

	//Enable sys cfg clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//Set usb base
	base = USB_OTG_FS;

	//Set usb device
	device = (USB_OTG_DeviceTypeDef *)((uint32_t)base + USB_OTG_DEVICE_BASE);

	//Set usb pcgcctl
	pcgcctl = (volatile uint32_t *)((uint32_t)base + USB_OTG_PCGCCTL_BASE);
	
	//Disable interrupt
	DisableInterrupt();

	//Init usb core
	InitUsbCore();

	//Set device mode
	ConfigDeviceMode();

	//Init usb device
	InitUsbDevice();
}


/// @brief Init usb core
void Usb::InitUsbCore()
{
	//Select FS Embedded PHY
    base->GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL;

	//Wait for AHB master IDLE state.
	while ((base->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);

	//Core Soft Reset
	base->GRSTCTL |= USB_OTG_GRSTCTL_CSRST;

	//Wait for reset.
	while ((base->GRSTCTL & USB_OTG_GRSTCTL_CSRST) == USB_OTG_GRSTCTL_CSRST);

	//Deactivate the USB Transceiver
    base->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);
}


/// @brief Config device mode
void Usb::ConfigDeviceMode()
{
	uint32_t ms = 0U;

	base->GUSBCFG &= ~(USB_OTG_GUSBCFG_FHMOD | USB_OTG_GUSBCFG_FDMOD);

	base->GUSBCFG |= USB_OTG_GUSBCFG_FDMOD;

	do
	{
		HAL_Delay(1U);
		ms++;
	} while ((GetMode() != Usb::_DeviceMode) && (ms < 50U));
}


/// @brief Config host mode
/// @param mode 
void Usb::ConfigHostMode()
{
	uint32_t ms = 0U;

	base->GUSBCFG &= ~(USB_OTG_GUSBCFG_FHMOD | USB_OTG_GUSBCFG_FDMOD);

	base->GUSBCFG |= USB_OTG_GUSBCFG_FHMOD;

	do
	{
		HAL_Delay(1U);
		ms++;
	} while ((GetMode() != Usb::_HostMode) && (ms < 50U));
}


/// @brief Get mode
/// @return 
Usb::Mode Usb::GetMode()
{
	return (Mode)((base->GINTSTS) & 0x1U);
}


/// @brief In endpoint
/// @param i 
/// @return 
USB_OTG_INEndpointTypeDef* Usb::InEndPoint(uint8_t index)
{
	return (USB_OTG_INEndpointTypeDef *)((uint32_t)base + USB_OTG_IN_ENDPOINT_BASE + ((index) * USB_OTG_EP_REG_SIZE));
}


/// @brief Out endpoint
/// @param i 
/// @return 
USB_OTG_OUTEndpointTypeDef* Usb::OutEndPoint(uint8_t index)
{
	return ((USB_OTG_OUTEndpointTypeDef *)((uint32_t)base + USB_OTG_OUT_ENDPOINT_BASE + ((index) * USB_OTG_EP_REG_SIZE)));
}


/// @brief Init usb device
void Usb::InitUsbDevice()
{
	for (uint8_t i = 0U; i < 15U; i++)
	{
		base->DIEPTXF[i] = 0U;
	}

	//VBUS Sensing setup
    //Disable HW VBUS sensing. VBUS is internally considered to be always
    //at VBUS-Valid level (5V).
    device->DCTL |= USB_OTG_DCTL_SDIS;
    base->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
    base->GCCFG &= ~USB_OTG_GCCFG_VBUSBSEN;
    base->GCCFG &= ~USB_OTG_GCCFG_VBUSASEN;

	//Restart the Phy Clock
	*pcgcctl = 0U;

	//Device mode configuration
	device->DCFG |= DCFG_FRAME_INTERVAL_80;

	//Set Core speed to Full speed mode
	ConfigDevSpeed(Usb::_SpeedFull);

	//Flush the tx FIFOs
	FlushTxFifo(0x10U);

	//Flush the rx FIFOs
	FlushRxFifo();

	//Clear all pending Device Interrupts
	device->DIEPMSK = 0U;
	device->DOEPMSK = 0U;
	device->DAINTMSK = 0U;

	//Init endpoint
	InitEndpoint(dev_endpoints);

	//Clear tx interrupt
	device->DIEPMSK &= ~(USB_OTG_DIEPMSK_TXFURM);

	//Disable all interrupts.
	base->GINTMSK = 0U;

	//Clear any pending interrupts
	base->GINTSTS = 0xBFFFFFFFU;

	//Enable the common interrupts
	base->GINTMSK |= USB_OTG_GINTMSK_RXFLVLM;

	//Enable interrupts matching to the Device mode ONLY
	base->GINTMSK |= USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_USBRST |
					USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_IEPINT |
					USB_OTG_GINTMSK_OEPINT   | USB_OTG_GINTMSK_IISOIXFRM |
					USB_OTG_GINTMSK_PXFRM_IISOOXFRM | USB_OTG_GINTMSK_WUIM;

	//Enable Sof interrupt
	base->GINTMSK |= USB_OTG_GINTMSK_SOFM;

	//Disconnect device
	DisconnectDevice();
}


/// @brief Init endpoint
/// @param endpoints 
void Usb::InitEndpoint(uint8_t endpoints)
{
	for (uint8_t i = 0U; i < endpoints; i++)
	{
		if ((InEndPoint(i)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
		{
			if (i == 0U)
			{
				InEndPoint(i)->DIEPCTL = USB_OTG_DIEPCTL_SNAK;
			}
			else
			{
				InEndPoint(i)->DIEPCTL = USB_OTG_DIEPCTL_EPDIS | USB_OTG_DIEPCTL_SNAK;
			}
		}
		else
		{
			InEndPoint(i)->DIEPCTL = 0U;
		}

		InEndPoint(i)->DIEPTSIZ = 0U;
		InEndPoint(i)->DIEPINT  = 0xFB7FU;
	}

	for (uint8_t i = 0U; i < endpoints; i++)
	{
		if ((OutEndPoint(i)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
		{
			if (i == 0U)
			{
				OutEndPoint(i)->DOEPCTL = USB_OTG_DOEPCTL_SNAK;
			}
			else
			{
				OutEndPoint(i)->DOEPCTL = USB_OTG_DOEPCTL_EPDIS | USB_OTG_DOEPCTL_SNAK;
			}
		}
		else
		{
			OutEndPoint(i)->DOEPCTL = 0U;
		}

		OutEndPoint(i)->DOEPTSIZ = 0U;
		OutEndPoint(i)->DOEPINT  = 0xFB7FU;
	}
}


/// @brief Config device speed
/// @param speed 
void Usb::ConfigDevSpeed(uint8_t speed)
{
	device->DCFG |= speed;
}


/// @brief Config tx fifo
/// @param fifo 
/// @param size 
//  TXn min size = 16 words. (n  : Transmit FIFO index)
//	When a TxFIFO is not used, the Configuration should be as follows:
//		case 1 :  n > m    and Txn is not used    (n,m  : Transmit FIFO indexes)
//		--> Txm can use the space allocated for Txn.
//		case2  :  n < m    and Txn is not used    (n,m  : Transmit FIFO indexes)
//		--> Txn should be configured with the minimum space of 16 words
//	The FIFO is used optimally when used TxFIFOs are allocated in the top
//		of the FIFO.Ex: use EP1 and EP2 as IN instead of EP1 and EP3 as IN ones.
//	When DMA is used 3n * FIFO locations should be reserved for internal DMA registers
void Usb::ConfigTxFifo(uint8_t fifo, uint16_t size)
{
	uint8_t i;
	uint32_t txOffset;

	txOffset = base->GRXFSIZ;

	if (fifo == 0U)
	{
		base->DIEPTXF0_HNPTXFSIZ = ((uint32_t)size << 16) | txOffset;
	}
	else
	{
		txOffset += (base->DIEPTXF0_HNPTXFSIZ) >> 16;
		
		for (i = 0U; i < (fifo - 1U); i++)
		{
			txOffset += (base->DIEPTXF[i] >> 16);
		}

		// Multiply Tx_Size by 2 to get higher performance
		base->DIEPTXF[fifo - 1U] = ((uint32_t)size << 16) | txOffset;
	}
}


/// @brief Config rx fifo
/// @param size 
void Usb::ConfigRxFifo(uint16_t size)
{
	base->GRXFSIZ = size;
}


/// @brief Flush tx fifo
void Usb::FlushTxFifo(uint32_t num)
{
	while ((base->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);
	base->GRSTCTL = (USB_OTG_GRSTCTL_TXFFLSH | (num << 6));
	while ((base->GRSTCTL & USB_OTG_GRSTCTL_TXFFLSH) == USB_OTG_GRSTCTL_TXFFLSH);
}


/// @brief Flush rx fifo
void Usb::FlushRxFifo()
{
	while ((base->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);
	base->GRSTCTL = USB_OTG_GRSTCTL_RXFFLSH;
	while ((base->GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH) == USB_OTG_GRSTCTL_RXFFLSH);
}


/// @brief Connect device
void Usb::ConnectDevice()
{
	//In case phy is stopped, ensure to ungate and restore the phy CLK
	*pcgcctl &= ~(USB_OTG_PCGCCTL_STOPCLK | USB_OTG_PCGCCTL_GATECLK);

	device->DCTL &= ~USB_OTG_DCTL_SDIS;
}


/// @brief Disconnect device
void Usb::DisconnectDevice()
{
	//In case phy is stopped, ensure to ungate and restore the phy CLK
	*pcgcctl &= ~(USB_OTG_PCGCCTL_STOPCLK | USB_OTG_PCGCCTL_GATECLK);

	device->DCTL |= USB_OTG_DCTL_SDIS;
}


/// @brief Enable interrupt
/// @param enable 
void Usb::EnableInterrupt()
{
	base->GAHBCFG |= USB_OTG_GAHBCFG_GINT;
}


/// @brief Disable interrupt
void Usb::DisableInterrupt()
{
	base->GAHBCFG &= ~USB_OTG_GAHBCFG_GINT;
}


/// @brief Enable
void Usb::Enable()
{
	//Enable USB Transceiver
	base->GCCFG |= USB_OTG_GCCFG_PWRDWN;
}


/// @brief Start
void Usb::Start()
{
	Enable();
	EnableInterrupt();
	ConnectDevice();
}


/// @brief IRQ handler
void Usb::IRQHandler()
{
	if (Usb::_DeviceMode == GetMode())
	{
		
	}
}
