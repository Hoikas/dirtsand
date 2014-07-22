/******************************************************************************
 * This file is part of dirtsand.                                             *
 *                                                                            *
 * dirtsand is free software: you can redistribute it and/or modify           *
 * it under the terms of the GNU Affero General Public License as             *
 * published by the Free Software Foundation, either version 3 of the         *
 * License, or (at your option) any later version.                            *
 *                                                                            *
 * dirtsand is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Affero General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the GNU Affero General Public License   *
 * along with dirtsand.  If not, see <http://www.gnu.org/licenses/>.          *
 ******************************************************************************/

#ifndef _MOUL_CLIENTGUID_H
#define _MOUL_CLIENTGUID_H

#include "strings.h"
#include "Types/Uuid.h"

namespace MOUL
{
    struct ClientGuid
    {
        enum Contents
        {
            e_HasAcctUuid       = (1<<0),
            e_HasPlayerId       = (1<<1),
            e_HasTempPlayerId   = (1<<2),
            e_HasCCRLevel       = (1<<3),
            e_HasProtectedLogin = (1<<4),
            e_HasBuildType      = (1<<5),
            e_HasPlayerName     = (1<<6),
            e_HasSrcAddr        = (1<<7),
            e_HasSrcPort        = (1<<8),
            e_HasReserved       = (1<<9),
            e_HasClientKey      = (1<<10),
        };

        uint16_t m_flags;

        #define CLI_FIELD(type, name) \
            type m_##name; \
            void set_##name(type value) \
            { \
                m_##name = value; \
                m_flags |= e_Has##name; \
            } \
            bool has_##name() const { return (m_flags & e_Has##name) != 0; }
        CLI_FIELD(DS::Uuid, AcctUuid)
        CLI_FIELD(uint32_t, PlayerId)
        CLI_FIELD(DS::String, PlayerName)
        CLI_FIELD(uint8_t, CCRLevel)
        CLI_FIELD(bool, ProtectedLogin)
        CLI_FIELD(uint8_t, BuildType)
        CLI_FIELD(uint32_t, SrcAddr)
        CLI_FIELD(uint16_t, SrcPort)
        CLI_FIELD(uint16_t, Reserved)
        CLI_FIELD(DS::String, ClientKey)
        #undef CLI_FIELD

        void read(DS::Stream* stream);
        void write(DS::Stream* stream) const;

        ClientGuid() : m_flags() { }
    };
}

#endif
