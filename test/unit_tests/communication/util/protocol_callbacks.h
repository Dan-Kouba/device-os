/*
 * Copyright (c) 2020 Particle Industries, Inc.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "spark_protocol_functions.h"

#include "system_tick_hal.h"

#include <functional>

namespace particle::protocol::test {

// Helper class for mocking the protocol callbacks
class Callbacks {
public:
    Callbacks();
    virtual ~Callbacks();

    Callbacks& setMillis(system_tick_t ms);
    Callbacks& addMillis(system_tick_t ms);

    const SparkCallbacks& get() const;

    virtual int send(const uint8_t* buf, uint32_t bufSize, void* ctx);
    virtual int receive(uint8_t *buf, uint32_t bufSize, void* ctx);
#if HAL_PLATFORM_OTA_PROTOCOL_V3
    virtual int startFirmwareUpdate(size_t fileSize, const char* fileHash, size_t* fileOffset, unsigned flags);
    virtual int finishFirmwareUpdate(unsigned flags);
    virtual int saveFirmwareChunk(const char* chunkData, size_t chunkSize, size_t chunkOffset, size_t partialSize);
#else
    virtual int prepareForFirmwareUpdate(FileTransfer::Descriptor& data, uint32_t flags, void* reserved);
    virtual int saveFirmwareChunk(FileTransfer::Descriptor& descriptor, const uint8_t* chunk, void* reserved);
    virtual int finishFirmwareUpdate(FileTransfer::Descriptor& data, uint32_t flags, void* reserved);
#endif // !HAL_PLATFORM_OTA_PROTOCOL_V3
    virtual uint32_t calculateCrc(const uint8_t *buf, uint32_t bufSize);
    virtual void signal(bool on, unsigned param, void* reserved);
    virtual system_tick_t millis();
    virtual void setTime(uint32_t time, unsigned param, void* reserved);
    virtual int save(const void* data, size_t size, uint8_t type, void* reserved);
    virtual int restore(void* data, size_t size, uint8_t type, void* reserved);
    virtual void notifyClientMessagesProcessed(void* reserved);

private:
    SparkCallbacks cb_;
    system_tick_t millis_;
};

inline Callbacks& Callbacks::setMillis(system_tick_t ms) {
    millis_ = ms;
    return *this;
}

inline Callbacks& Callbacks::addMillis(system_tick_t ms) {
    millis_ += ms;
    return *this;
}

inline const SparkCallbacks& Callbacks::get() const {
    return cb_;
}

inline int Callbacks::send(const uint8_t* buf, uint32_t bufSize, void* ctx) {
    return bufSize;
}

inline int Callbacks::receive(uint8_t *buf, uint32_t bufSize, void* ctx) {
    return 0;
}

#if HAL_PLATFORM_OTA_PROTOCOL_V3

inline int Callbacks::startFirmwareUpdate(size_t fileSize, const char* fileHash, size_t* fileOffset, unsigned flags) {
    return 0;
}

inline int Callbacks::finishFirmwareUpdate(unsigned flags) {
    return 0;
}

inline int Callbacks::saveFirmwareChunk(const char* chunkData, size_t chunkSize, size_t chunkOffset, size_t partialSize) {
    return 0;
}

#else

inline int Callbacks::prepareForFirmwareUpdate(FileTransfer::Descriptor& data, uint32_t flags, void* reserved) {
    return 0;
}

inline int Callbacks::saveFirmwareChunk(FileTransfer::Descriptor& descriptor, const uint8_t* chunk, void* reserved) {
    return 0;
}

inline int Callbacks::finishFirmwareUpdate(FileTransfer::Descriptor& data, uint32_t flags, void* reserved) {
    return 0;
}

#endif // !HAL_PLATFORM_OTA_PROTOCOL_V3

inline uint32_t Callbacks::calculateCrc(const uint8_t *buf, uint32_t bufSize) {
    return 0;
}

inline void Callbacks::signal(bool on, unsigned param, void* reserved) {
}

inline system_tick_t Callbacks::millis() {
    return millis_;
}

inline void Callbacks::setTime(uint32_t time, unsigned param, void* reserved) {
}

inline int Callbacks::save(const void* data, size_t size, uint8_t type, void* reserved) {
    return 0;
}

inline int Callbacks::restore(void* data, size_t size, uint8_t type, void* reserved) {
    return 0;
}

inline void Callbacks::notifyClientMessagesProcessed(void* reserved) {
}

} // namespace particle::protocol::test
