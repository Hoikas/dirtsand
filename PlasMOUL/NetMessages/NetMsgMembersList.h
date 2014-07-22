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

#ifndef _MOUL_NETMSGMEMBERSLIST_H
#define _MOUL_NETMSGMEMBERSLIST_H

#include "ClientGuid.h"
#include "NetMessage.h"
#include "Key.h"
#include <vector>

namespace MOUL
{
    struct NetMsgMemberInfo
    {
        uint32_t m_flags;
        ClientGuid m_client;
        Uoid m_avatarKey;

        NetMsgMemberInfo() : m_flags() { }

        void read(DS::Stream* stream);
        void write(DS::Stream* stream) const;
    };

    class NetMsgMembersListReq : public NetMessage
    {
        FACTORY_CREATABLE(NetMsgMembersListReq)

    protected:
        NetMsgMembersListReq(uint16_t type) : NetMessage(type) { }
    };

    class NetMsgMembersList : public NetMsgServerToClient
    {
        FACTORY_CREATABLE(NetMsgMembersList)

        std::vector<NetMsgMemberInfo> m_members;

        virtual void read(DS::Stream* stream);
        virtual void write(DS::Stream* stream) const;

    protected:
        NetMsgMembersList(uint16_t type) : NetMsgServerToClient(type) { }
    };

    class NetMsgMemberUpdate : public NetMsgServerToClient
    {
        FACTORY_CREATABLE(NetMsgMemberUpdate)

        NetMsgMemberInfo m_member;
        bool m_addMember;

        virtual void read(DS::Stream* stream);
        virtual void write(DS::Stream* stream) const;

    protected:
        NetMsgMemberUpdate(uint16_t type)
            : NetMsgServerToClient(type), m_addMember() { }
    };
}

#endif
