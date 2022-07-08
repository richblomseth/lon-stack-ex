/* sockLib.h -  UNIX BSD 4.3 compatible socket library header */

/*
 * Copyright 1984-1995 Wind River Systems, Inc. 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in 
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
modification history
--------------------
02f,25jul95,dzb  added prototype for sockLibAdd().
02e,24jul95,dzb  changed sockInit() to sockLibInit().
02d,23jul93,jmm  changed #include "socket.h" to "sys/socket.h" (spr 2033)
02c,22sep92,rrr  added support for c++
02b,19aug92,smb  changed systime.h to sys/times.h
02a,04jul92,jcf  cleaned up.
01e,26may92,rrr  the tree shuffle
01d,16dec91,gae  added includes for ANSI.
01c,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01b,23oct90,shl replaced all occurances of "int flag s" to "int s".
01a,05oct90,shl created.
*/

#ifndef __INCsockLibh
#define __INCsockLibh

#ifdef __cplusplus
extern "C" {
#endif

#include "sys/times.h"
#include "sys/socket.h"

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	sockLibInit (int fdMax);
extern STATUS 	sockLibAdd (FUNCPTR sockLibInitRtn, int domainMap,
		    int domainReal);
extern STATUS 	bind (int s, struct sockaddr *name, int namelen);
extern STATUS 	connect (int s, struct sockaddr *name, int namelen);
extern STATUS 	connectWithTimeout (int sock, struct sockaddr *adrs,
				    int adrsLen, struct timeval *timeVal);
extern STATUS 	getpeername (int s, struct sockaddr *name, int *namelen);
extern STATUS 	getsockname (int s, struct sockaddr *name, int *namelen);
extern STATUS 	getsockopt (int s, int level, int optname, char *optval,
			    int *optlen);
extern STATUS 	listen (int s, int backlog);
extern STATUS 	setsockopt (int s, int level, int optname, char *optval,
			    int optlen);
extern STATUS 	shutdown (int s, int how);
extern int 	accept (int s, struct sockaddr *addr, int *addrlen);
extern int 	recv (int s, char *buf, int bufLen, int flags);
extern int 	recvfrom (int s, char *buf, int bufLen, int flags,
			  struct sockaddr *from, int *pFromLen);
extern int 	recvmsg (int sd, struct msghdr *mp, int flags);
extern int 	send (int s, char *buf, int bufLen, int flags);
extern int 	sendmsg (int sd, struct msghdr *mp, int flags);
extern int 	sendto (int s, caddr_t buf, int bufLen, int flags,
			struct sockaddr *to, int tolen);
extern int 	socket (int domain, int type, int protocol);

#else	/* __STDC__ */

extern STATUS 	sockLibInit ();
extern STATUS 	sockLibAdd ();
extern STATUS 	bind ();
extern STATUS 	connect ();
extern STATUS 	connectWithTimeout ();
extern STATUS 	getpeername ();
extern STATUS 	getsockname ();
extern STATUS 	getsockopt ();
extern STATUS 	listen ();
extern STATUS 	setsockopt ();
extern STATUS 	shutdown ();
extern int 	accept ();
extern int 	recv ();
extern int 	recvfrom ();
extern int 	recvmsg ();
extern int 	send ();
extern int 	sendmsg ();
extern int 	sendto ();
extern int 	socket ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCsockLibh */
