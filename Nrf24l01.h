#pragma once

#include "INrf24.h"
#include "IGpioDriver.h"
#include "ITransport.h"

namespace nrf24l01_driver {

#define REGISTER_READ_BASE_ADDRESS 0x00
#define REGISTER_WRITE_BASE_ADDRESS 0x20

enum RegisterMap {
    REGISTER_CONFIG         = 0x00,
    REGISTER_EN_AA          = 0x01,
    REGISTER_EN_RXADDR      = 0x02,
    REGISTER_SETUP_AW       = 0x03,
    REGISTER_SETUP_RETR     = 0x04,
    REGISTER_RF_CH          = 0x05,
    REGISTER_RF_SETUP       = 0x06,
    REGISTER_STATUS         = 0x07,
    REGISTER_OBSERVE_TX     = 0x08,
    REGISTER_CD             = 0x09,
    REGISTER_RX_ADDR_P0     = 0x0A,
    REGISTER_RX_ADDR_P1     = 0x0B,
    REGISTER_RX_ADDR_P2     = 0x0C,
    REGISTER_RX_ADDR_P3     = 0x0D,
    REGISTER_RX_ADDR_P4     = 0x0E,
    REGISTER_RX_ADDR_P5     = 0x0F,
    REGISTER_TX_ADDR        = 0x10,
    REGISTER_RX_PW_P0       = 0x11,
    REGISTER_RX_PW_P1       = 0x12,
    REGISTER_RX_PW_P2       = 0x13,
    REGISTER_RX_PW_P3       = 0x14,
    REGISTER_RX_PW_P4       = 0x15,
    REGISTER_RX_PW_P5       = 0x16,
    REGISTER_FIFO_STATUS    = 0x17,
    REGISTER_DYNPD          = 0x1C,
    REGISTER_FEATURE        = 0x1D,
    REGISTER_NUM,
};

class Nrf24l01 : public nrf24_driver::INrf24 {

public:

    Nrf24l01(
            transport::ITransport *transport,
            gpio_driver::IGpio *chip_enable);

    virtual Status SetDefaults(void);
    virtual Status SetRfChannel(uint8_t channel);
    virtual Status SetPayloadSize(uint8_t payload_size);
    virtual Status SetPayloadSize(nrf24_driver::Rx rx, uint8_t payload_size);
    virtual Status SetRetries(uint8_t delay, uint8_t retries);
    virtual Status SetRxAddress(nrf24_driver::Rx rx, uint8_t address[], uint8_t size);
    virtual Status SetTxAddress(nrf24_driver::Tx tx, uint8_t address[], uint8_t size);

private:
    transport::ITransport *transport_;
    gpio_driver::IGpio *chip_enable_;

    uint8_t GetWriteAddress(RegisterMap rm);
    uint8_t GetReadAddress(RegisterMap rm);
    uint8_t GetPipeNumber(nrf24_driver::Rx);
};

} /*namespace nrf24l01_driver*/
