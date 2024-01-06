#ifndef __I386_H__
#define __I386_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PIC defines */
#define PIC1                                 0x20             /* IO base address for master PIC */
#define PIC2                                 0xA0             /* IO base address for slave PIC */
#define PIC1_CMD                             PIC1
#define PIC1_DATA                            (PIC1 + 1)
#define PIC2_CMD                             PIC2
#define PIC2_DATA                            (PIC2 + 1)
#define PIC_EOI                              0x20

#define PIC_READ_IRR                         0x0a            /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                         0x0b            /* OCW3 irq service next CMD read */

#define ICW1_ICW4                            0x01            /* Indicates that ICW4 will be present */
#define ICW1_SINGLE                          0x02            /* Single (cascade) mode */
#define ICW1_INTERVAL4                       0x04            /* Call address interval 4 (8) */
#define ICW1_LEVEL                           0x08            /* Level triggered (edge) mode */
#define ICW1_INIT                            0x10            /* Initialization - required! */
 
#define ICW4_8086                            0x01            /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO                            0x02            /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE                       0x08            /* Buffered mode/slave */
#define ICW4_BUF_MASTER                      0x0C            /* Buffered mode/master */
#define ICW4_SFNM                            0x10            /* Special fully nested (not) */

/* Timer defines */
#define TIMER                                0x40
#define TIMER_CH0                            (TIMER + 0)
#define TIMER_CH1                            (TIMER + 1)
#define TIMER_CH2                            (TIMER + 2)
#define TIMER_CMD                            (TIMER + 3)

/* Serial port defines */
#define COM1                                 0x3f8
#define COM2                                 0x2f8
#define COM3                                 0x3e8
#define COM4                                 0x2e8
#define COM5                                 0x5f8
#define COM6                                 0x4f8
#define COM7                                 0x5e8
#define COM8                                 0x4e8

#define COM_DATA_Pos                         (0)
#define COM_IT_ENA_Pos                       (1)
#define COM_LO_BAUD_Pos                      (0)
#define COM_HI_BAUD_Pos                      (1)
#define COM_IT_FIFO_Pos                      (2)
#define COM_LINE_CTRL_Pos                    (3)
#define COM_MODEM_CTRL_Pos                   (4)
#define COM_LINE_STATUS_Pos                  (5)
#define COM_MODEM_STATUS_Pos                 (6)
#define COM_SCRATCH_Pos                      (7)

#define COM1_DATA                            (COM1 + 0)
#define COM1_IT_ENA_REG                      (COM1 + 1)
#define COM1_LO_BAUD_REG                     (COM1 + 0)
#define COM1_HI_BAUD_REG                     (COM1 + 1)
#define COM1_IT_FIFO_REG                     (COM1 + 2)
#define COM1_LINE_CTRL_REG                   (COM1 + 3)
#define COM1_MODEM_CTRL_REG                  (COM1 + 4)
#define COM1_LINE_STATUS_REG                 (COM1 + 5)
#define COM1_MODEM_STATUS_REG                (COM1 + 6)
#define COM1_SCRATCH_REG                     (COM1 + 7)

#define COM2_DATA                            (COM2 + 0)
#define COM2_IT_ENA_REG                      (COM2 + 1)
#define COM2_LO_BAUD_REG                     (COM2 + 0)
#define COM2_HI_BAUD_REG                     (COM2 + 1)
#define COM2_IT_FIFO_REG                     (COM2 + 2)
#define COM2_LINE_CTRL_REG                   (COM2 + 3)
#define COM2_MODEM_CTRL_REG                  (COM2 + 4)
#define COM2_LINE_STATUS_REG                 (COM2 + 5)
#define COM2_MODEM_STATUS_REG                (COM2 + 6)
#define COM2_SCRATCH_REG                     (COM2 + 7)

#define COM3_DATA                            (COM3 + 0)
#define COM3_IT_ENA_REG                      (COM3 + 1)
#define COM3_LO_BAUD_REG                     (COM3 + 0)
#define COM3_HI_BAUD_REG                     (COM3 + 1)
#define COM3_IT_FIFO_REG                     (COM3 + 2)
#define COM3_LINE_CTRL_REG                   (COM3 + 3)
#define COM3_MODEM_CTRL_REG                  (COM3 + 4)
#define COM3_LINE_STATUS_REG                 (COM3 + 5)
#define COM3_MODEM_STATUS_REG                (COM3 + 6)
#define COM3_SCRATCH_REG                     (COM3 + 7)

#define COM4_DATA                            (COM4 + 0)
#define COM4_IT_ENA_REG                      (COM4 + 1)
#define COM4_LO_BAUD_REG                     (COM4 + 0)
#define COM4_HI_BAUD_REG                     (COM4 + 1)
#define COM4_IT_FIFO_REG                     (COM4 + 2)
#define COM4_LINE_CTRL_REG                   (COM4 + 3)
#define COM4_MODEM_CTRL_REG                  (COM4 + 4)
#define COM4_LINE_STATUS_REG                 (COM4 + 5)
#define COM4_MODEM_STATUS_REG                (COM4 + 6)
#define COM4_SCRATCH_REG                     (COM4 + 7)

#define COM5_DATA                            (COM5 + 0)
#define COM5_IT_ENA_REG                      (COM5 + 1)
#define COM5_LO_BAUD_REG                     (COM5 + 0)
#define COM5_HI_BAUD_REG                     (COM5 + 1)
#define COM5_IT_FIFO_REG                     (COM5 + 2)
#define COM5_LINE_CTRL_REG                   (COM5 + 3)
#define COM5_MODEM_CTRL_REG                  (COM5 + 4)
#define COM5_LINE_STATUS_REG                 (COM5 + 5)
#define COM5_MODEM_STATUS_REG                (COM5 + 6)
#define COM5_SCRATCH_REG                     (COM5 + 7)

#define COM6_DATA                            (COM6 + 0)
#define COM6_IT_ENA_REG                      (COM6 + 1)
#define COM6_LO_BAUD_REG                     (COM6 + 0)
#define COM6_HI_BAUD_REG                     (COM6 + 1)
#define COM6_IT_FIFO_REG                     (COM6 + 2)
#define COM6_LINE_CTRL_REG                   (COM6 + 3)
#define COM6_MODEM_CTRL_REG                  (COM6 + 4)
#define COM6_LINE_STATUS_REG                 (COM6 + 5)
#define COM6_MODEM_STATUS_REG                (COM6 + 6)
#define COM6_SCRATCH_REG                     (COM6 + 7)

#define COM7_DATA                            (COM7 + 0)
#define COM7_IT_ENA_REG                      (COM7 + 1)
#define COM7_LO_BAUD_REG                     (COM7 + 0)
#define COM7_HI_BAUD_REG                     (COM7 + 1)
#define COM7_IT_FIFO_REG                     (COM7 + 2)
#define COM7_LINE_CTRL_REG                   (COM7 + 3)
#define COM7_MODEM_CTRL_REG                  (COM7 + 4)
#define COM7_LINE_STATUS_REG                 (COM7 + 5)
#define COM7_MODEM_STATUS_REG                (COM7 + 6)
#define COM7_SCRATCH_REG                     (COM7 + 7)

#define COM8_DATA                            (COM8 + 0)
#define COM8_IT_ENA_REG                      (COM8 + 1)
#define COM8_LO_BAUD_REG                     (COM8 + 0)
#define COM8_HI_BAUD_REG                     (COM8 + 1)
#define COM8_IT_FIFO_REG                     (COM8 + 2)
#define COM8_LINE_CTRL_REG                   (COM8 + 3)
#define COM8_MODEM_CTRL_REG                  (COM8 + 4)
#define COM8_LINE_STATUS_REG                 (COM8 + 5)
#define COM8_MODEM_STATUS_REG                (COM8 + 6)
#define COM8_SCRATCH_REG                     (COM8 + 7)

#define COM_LINE_CTRL_DATA_BITS_Pos          (0)
#define COM_LINE_CTRL_DATA_BITS_Msk          (0x3 << COM_LINE_CTRL_DATA_BITS_Pos)
#define COM_LINE_CTRL_DATA_BITS              COM_LINE_CTRL_DATA_BITS_Msk
#define COM_LINE_CTRL_DATA_BITS_0            (0x1 << COM_LINE_CTRL_DATA_BITS_Pos)
#define COM_LINE_CTRL_DATA_BITS_1            (0x2 << COM_LINE_CTRL_DATA_BITS_Pos)

#define COM_LINE_CTRL_STOP_BITS_Pos          (2)
#define COM_LINE_CTRL_STOP_BITS_Msk          (0x1 << COM_LINE_CTRL_STOP_BITS_Pos)
#define COM_LINE_CTRL_STOP_BITS              COM_LINE_CTRL_STOP_BITS_Msk

#define COM_LINE_CTRL_PARITY_Pos             (3)
#define COM_LINE_CTRL_PARITY_Msk             (0x7 << COM_LINE_CTRL_PARITY_Pos)
#define COM_LINE_CTRL_PARITY                 COM_LINE_CTRL_PARITY_Msk
#define COM_LINE_CTRL_PARITY_0               (0x1 << COM_LINE_CTRL_PARITY_Pos)
#define COM_LINE_CTRL_PARITY_1               (0x2 << COM_LINE_CTRL_PARITY_Pos)
#define COM_LINE_CTRL_PARITY_2               (0x4 << COM_LINE_CTRL_PARITY_Pos)

#define COM_IT_ENA_TYPE_Pos                  (0)
#define COM_IT_ENA_TYPE_Msk                  (0xf << COM_IT_ENA_TYPE_Pos)
#define COM_IT_ENA_TYPE                      COM_IT_ENA_TYPE_Msk
#define COM_IT_ENA_TYPE_0                    (0x1 << COM_IT_ENA_TYPE_Pos)
#define COM_IT_ENA_TYPE_1                    (0x2 << COM_IT_ENA_TYPE_Pos)
#define COM_IT_ENA_TYPE_2                    (0x4 << COM_IT_ENA_TYPE_Pos)
#define COM_IT_ENA_TYPE_3                    (0x8 << COM_IT_ENA_TYPE_Pos)

#define COM_MODEM_CTRL_DTR_Pos               (0)
#define COM_MODEM_CTRL_DTR_Msk               (0x1 << COM_MODEM_CTRL_DTR_Pos)
#define COM_MODEM_CTRL_DTR                   COM_MODEM_CTRL_DTR_Msk
#define COM_MODEM_CTRL_RTS_Pos               (1)
#define COM_MODEM_CTRL_RTS_Msk               (0x1 << COM_MODEM_CTRL_RTS_Pos)
#define COM_MODEM_CTRL_RTS                   COM_MODEM_CTRL_RTS_Msk
#define COM_MODEM_CTRL_OUT1_Pos              (2)
#define COM_MODEM_CTRL_OUT1_Msk              (0x1 << COM_MODEM_CTRL_OUT1_Pos)
#define COM_MODME_CTRL_OUT1                  COM_MODEM_CTRL_OUT1_Msk
#define COM_MODEM_CTRL_OUT2_Pos              (3)
#define COM_MODEM_CTRL_OUT2_Msk              (0x1 << COM_MODEM_CTRL_OUT2_Pos)
#define COM_MODEM_CTRL_OUT2                  COM_MODEM_CTRL_OUT2_Msk
#define COM_MODEM_CTRL_LOOP_Pos              (4)
#define COM_MODEM_CTRL_LOOP_Msk              (0x1 << COM_MODEM_CTRL_LOOP_Pos)
#define COM_MODEM_CTRL_LOOP                  COM_MODEM_CTRL_LOOP_Msk

#define COM_LINE_STATUS_DR_Pos               (0)
#define COM_LINE_STATUS_DR_Msk               (0x1 << COM_LINE_STATUS_DR_Pos)
#define COM_LINE_STATUS_DR                   COM_LINE_STATUS_DR_Msk
#define COM_LINE_STATUS_OE_Pos               (1)
#define COM_LINE_STATUS_OE_Msk               (0x1 << COM_LINE_STATUS_OE_Pos)
#define COM_LINE_STATUS_OE                   COM_LINE_STATUS_OE_Msk
#define COM_LINE_STATUS_PE_Pos               (2)
#define COM_LINE_STATUS_PE_Msk               (0x1 << COM_LINE_STATUS_PE_Pos)
#define COM_LINE_STATUS_PE                   COM_LINE_STATUS_PE_Msk
#define COM_LINE_STATUS_FE_Pos               (3)
#define COM_LINE_STATUS_FE_Msk               (0x1 << COM_LINE_STATUS_FE_Pos)
#define COM_LINE_STATUS_FE                   COM_LINE_STATUS_FE_Msk
#define COM_LINE_STATUS_BI_Pos               (4)
#define COM_LINE_STATUS_BI_Msk               (0x1 << COM_LINE_STATUS_BI_Pos)
#define COM_LINE_STATUS_BI                   COM_LINE_STATUS_BI_Msk
#define COM_LINE_STATUS_THRE_Pos             (5)
#define COM_LINE_STATUS_THRE_Msk             (0x1 << COM_LINE_STATUS_THRE_Pos)
#define COM_LINE_STATUS_THRE                 COM_LINE_STATUS_THRE_Msk
#define COM_LINE_STATUS_TEMT_Pos             (6)
#define COM_LINE_STATUS_TEMT_Msk             (0x1 << COM_LINE_STATUS_TEMT_Pos)
#define COM_LINE_STATUS_TEMT                 COM_LINE_STATUS_TEMT_Msk
#define COM_LINE_STATUS_IPE_Pos              (7)
#define COM_LINE_STATUS_IPE_Msk              (0x1 << COM_LINE_STATUS_IPE_Pos)
#define COM_LINE_STATUS_IPE                  COM_LINE_STATUS_IPE_Msk

#define COM_MODEM_STATUS_DCTS_Pos            (0)
#define COM_MODEM_STATUS_DCTS_Msk            (0x1 << COM_MODEM_STATUS_DCTS_Pos)
#define COM_MODEM_STATUS_DCTS                COM_MODEM_STATUS_DCTS_Msk
#define COM_MODEM_STATUS_DDSR_Pos            (1)
#define COM_MODEM_STATUS_DDSR_Msk            (0x1 << COM_MODEM_STATUS_DDSR_Pos)
#define COM_MODEM_STATUS_DDSR                COM_MODEM_STATUS_DDSR_Msk
#define COM_MODEM_STATUS_TERI_Pos            (2)
#define COM_MODEM_STATUS_TERI_Msk            (0x1 << COM_MODEM_STATUS_TERI_Pos)
#define COM_MODEM_STATUS_TERI                COM_MODEM_STATUS_TERI_Msk
#define COM_MODEM_STATUS_DDCD_Pos            (3)
#define COM_MODEM_STATUS_DDCD_Msk            (0x1 << COM_MODEM_STATUS_DDCD_Pos)
#define COM_MODEM_STATUS_DDCD                COM_MODEM_STATUS_DDCD_Msk
#define COM_MODEM_STATUS_CTS_Pos             (4)
#define COM_MODEM_STATUS_CTS_Msk             (0x1 << COM_MODEM_STATUS_CTS_Pos)
#define COM_MODEM_STATUS_CTS                 COM_MODEM_STATUS_CTS_Msk
#define COM_MODEM_STATUS_DSR_Pos             (5)
#define COM_MODEM_STATUS_DSR_Msk             (0x1 << COM_MODEM_STATUS_DSR_Pos)
#define COM_MODEM_STATUS_DSR                 COM_MODEM_STATUS_DSR_Msk
#define COM_MODEM_STATUS_RI_Pos              (6)
#define COM_MODEM_STATUS_RI_Msk              (0x1 << COM_MODEM_STATUS_RI_Pos)
#define COM_MODEM_STATUS_RI                  COM_MODEM_STATUS_RI_Msk
#define COM_MODEM_STATUS_DCD_Pos             (7)
#define COM_MODEM_STATUS_DCD_Msk             (0x1 << COM_MODEM_STATUS_DCD_Pos)
#define COM_MODEM_STATUS_DCD                 COM_MODEM_STATUS_DCD_Msk

/* LBA disk difines */
#define ATA                                  0x1f0
#define ATA_DATA                             (ATA + 0)
#define ATA_ERR                              (ATA + 1)
#define ATA_SECTOR_CNT                       (ATA + 2)
#define ATA_SECTOR_0_7_BITS                  (ATA + 3)
#define ATA_SECTOR_8_15_BITS                 (ATA + 4)
#define ATA_SECTOR_16_23_BITS                (ATA + 5)
#define ATA_MODE                             (ATA + 6)
#define ATA_CMD                              (ATA + 7)
#define ATA_STATUS                           (ATA + 7)

#define ATA_MODE_LBA                         (0xE0)
#define ATA_MODE_CHS                         (0xA0)
#define ATA_MODE_DRV_Pos                     (4)

#define ATA_CMD_READ                         (0x20)
#define ATA_CMD_WRITE                        (0x30)
#define ATA_CMD_FLUSH                        (0xE7)

#define ATA_STATUS_ERR_Pos                   (0)
#define ATA_STATUS_ERR_Msk                   (0x1 << ATA_STATUS_ERR_Pos)
#define ATA_STATUS_ERR                       ATA_STATUS_ERR_Msk
#define ATA_STATUS_IDX_Pos                   (1)
#define ATA_STATUS_IDX_Msk                   (0x1 << ATA_STATUS_IDX_Pos)
#define ATA_STATUS_IDX                       ATA_STATUS_IDX_Msk
#define ATA_STATUS_CORR_Pos                  (2)
#define ATA_STATUS_CORR_Msk                  (0x1 << ATA_STATUS_CORR_Pos)
#define ATA_STATUS_CORR                      ATA_STATUS_CORR_Msk
#define ATA_STATUS_DRQ_Pos                   (3)
#define ATA_STATUS_DRQ_Msk                   (0x1 << ATA_STATUS_DRQ_Pos)
#define ATA_STATUS_DRQ                       ATA_STATUS_DRQ_Msk
#define ATA_STATUS_SRV_Pos                   (4)
#define ATA_STATUS_SRV_Msk                   (0x1 << ATA_STATUS_SRV_Pos)
#define ATA_STATUS_SRV                       ATA_STATUS_SRV_Msk
#define ATA_STATUS_DF_Pos                    (5)
#define ATA_STATUS_DF_Msk                    (0x1 << ATA_STATUS_DF_Pos)
#define ATA_STATUS_DF                        ATA_STATUS_DF_Msk
#define ATA_STATUS_RDY_Pos                   (6)
#define ATA_STATUS_RDY_Msk                   (0x1 << ATA_STATUS_RDY_Pos)
#define ATA_STATUS_RDY                       ATA_STATUS_RDY_Msk
#define ATA_STATUS_BSY_Pos                   (7)
#define ATA_STATUS_BSY_Msk                   (0x1 << ATA_STATUS_BSY_Pos)
#define ATA_STATUS_BSY                       ATA_STATUS_BSY_Msk

/* IRQ numbers */
#define IRQ_Division_By_Zero                 0
#define IRQ_Debug                            1
#define IRQ_Non_Maskable_Interrupt           2
#define IRQ_Breakpoint                       3
#define IRQ_Into_Detected_Overflow           4
#define IRQ_Out_Of_Bounds                    5
#define IRQ_Invalid_Opcode                   6
#define IRQ_No_Coprocessor                   7
#define IRQ_Doule_Fault                      8
#define IRQ_Coprocessor_Segment_Overrun      9
#define IRQ_Bad_TSS                          10
#define IRQ_Segment_Not_Present              11
#define IRQ_Stack_Fault                      12
#define IRQ_General_Protection_Fault         13
#define IRQ_Page_Fault                       14
#define IRQ_Unknown_Interrupt                15
#define IRQ_Coprocessor_Fault                16
#define IRQ_Alignment_Check                  17
#define IRQ_Machine_Check                    18
#define IRQ_SVC                              30
#define IRQ_PendSV                           31

#define IRQ_Systick                          32
#define IRQ_Keyboard_Controller              33
#define IRQ_Serial_Port_COM2                 35
#define IRQ_Serial_Port_COM1                 36
#define IRQ_Line_Print_Terminal2             37
#define IRQ_Floppy_Controller                38
#define IRQ_Line_Print_Terminal1             39
#define IRQ_RTC_Timer                        40
#define IRQ_X86_Assembly_ACPI                41
#define IRQ_Mouse_Controller                 44
#define IRQ_Math_Coprocessor                 45
#define IRQ_ATA_Channel1                     46
#define IRQ_ATA_Channel2                     47

/* i386 utils */
#define low_8(address)   (uint8_t) ( (address) & 0xFF)
#define high_8(address)  (uint8_t) (((address) >> 8) & 0xFF)

#define low_16(address)  (uint16_t)( (address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

/* i386 low level function */
uint8_t PortByteIn(uint16_t port);
void PortByteOut(uint16_t port, uint8_t data);
uint16_t PortWordIn(uint16_t port);
void PortWordOut(uint16_t port, uint16_t data);

#ifdef __cplusplus
}
#endif

#endif //!__I386_H__
