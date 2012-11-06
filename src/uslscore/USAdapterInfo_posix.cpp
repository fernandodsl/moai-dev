/*	Useless Technologies - Version 1.0
	All contents Copyright (c) 2009 by Patrick Meehan
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

#include "pch.h"

#ifndef _WIN32

#include <uslscore/USAdapterInfo.h>

#ifndef NACL 
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <ifaddrs.h>
#if defined MOAI_OS_OSX || defined MOAI_OS_IPHONE 
#include <net/if_dl.h>
#elif defined MOAI_OS_LINUX || defined MOAI_OS_ANDROID 
#include <netpacket/packet.h>
#endif
#endif

//================================================================//
// USAdapterInfo
//================================================================//

//----------------------------------------------------------------//
void USAdapterInfo::SetNameFromMACAddress ( u8* address, u32 length ) {
	UNUSED ( address );
	UNUSED ( length );

	this->mName = "Unimplemented - Do Not Use!";
}

STLString USAdapterInfo::GetMACAddress () {

  USMacAddress macAddress;
  memset ( macAddress.bytes , 0 , 6 );

#ifndef NACL
  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    perror("getifaddrs");
    exit(EXIT_FAILURE);
  }

  /* Walk through linked list, maintaining head pointer so we
     can free list later */

  for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL)
      continue;

#if defined MOAI_OS_OSX || defined MOAI_OS_IPHONE 
    struct sockaddr_dl *socketStruct = (struct sockaddr_dl*) ifa->ifa_addr;
    if (sdl->sdl_family == AF_LINK) {
      memcpy ( macAddress.bytes, socketStruct->sdl_data + socketStruct->sdl_nlen, 6 );
      break;  // get the first addr
    }
#elif defined MOAI_OS_LINUX || defined MOAI_OS_ANDROID 
    if (ifa->ifa_addr->sa_family == AF_PACKET) {
      struct sockaddr_ll *socketStruct = (struct sockaddr_ll*) ifa->ifa_addr;
      memcpy ( macAddress.bytes, socketStruct->sll_addr, 6 );
      break;  // get the first addr
    }
#endif
  }
  freeifaddrs(ifaddr);
#endif

  char address[13];
  memset ( address , 0 , 13 );

  sprintf( address, "%02X%02X%02X%02X%02X%02X", macAddress.bytes[0], macAddress.bytes[1], macAddress.bytes[2], macAddress.bytes[3], macAddress.bytes[4], macAddress.bytes[5] );
  STLString macString = address;
  return macString;	
}
//================================================================//
// USAdapterInfoList
//================================================================//

//----------------------------------------------------------------//
void USAdapterInfoList::EnumerateAdapters () {

}

#endif

