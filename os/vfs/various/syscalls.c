/*
 ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "vfs.h"

#if !defined(SYSCALL_MAX_FDS)
#define SYSCALL_MAX_FDS                     10
#endif

static vfs_file_node_c *fds[SYSCALL_MAX_FDS];

static int translate_error(msg_t err) {

  err = -err - 32;

  return (int)err;
}

/***************************************************************************/

__attribute__((used))
int _open_r(struct _reent *r, const char *p, int oflag, int mode) {
  msg_t err;
  vfs_file_node_c *vfnp;
  int file;

  (void)mode;

  err = vfsOpenFile(p, oflag, &vfnp);
  if (err < VFS_RET_SUCCESS) {
    __errno_r(r) = translate_error(err);
    return -1;
  }

  /* Searching for a free file handle.*/
  for (file = 0; file < SYSCALL_MAX_FDS; file++) {
    if (fds[file] == NULL) {
      fds[file] = vfnp;
      return file;
    }
  }

  vfsCloseFile(vfnp);

  __errno_r(r) = translate_error(VFS_RET_EMFILE);
  return -1;
}

/***************************************************************************/

__attribute__((used))
int _close_r(struct _reent *r, int file) {

  if ((file < 0) || (file >= SYSCALL_MAX_FDS) || (fds[file] == NULL)) {
    __errno_r(r) = translate_error(VFS_RET_EBADF);
    return -1;
  }

  vfsCloseFile(fds[file]);
  fds[file] = NULL;

  return 0;
}

/***************************************************************************/

__attribute__((used))
int _read_r(struct _reent *r, int file, char *ptr, int len) {
  ssize_t nr;

  if ((file < 0) || (file >= SYSCALL_MAX_FDS) || (fds[file] == NULL)) {
    __errno_r(r) = translate_error(VFS_RET_EBADF);
    return -1;
  }

  nr = vfsReadFile(fds[file], (uint8_t *)ptr, (size_t)len);
  if (nr < VFS_RET_SUCCESS) {
    __errno_r(r) = translate_error((msg_t)nr);
    return -1;
  }

  return (int)nr;
}

/***************************************************************************/

__attribute__((used))
int _write_r(struct _reent *r, int file, const char *ptr, int len) {
  ssize_t nw;

  if ((file < 0) || (file >= SYSCALL_MAX_FDS) || (fds[file] == NULL)) {
    __errno_r(r) = translate_error(VFS_RET_EBADF);
    return -1;
  }

  nw = vfsWriteFile(fds[file], (const uint8_t *)ptr, (size_t)len);
  if (nw < VFS_RET_SUCCESS) {
    __errno_r(r) = translate_error((msg_t)nw);
    return -1;
  }

  return (int)nw;
}

/***************************************************************************/

__attribute__((used))
int _lseek_r(struct _reent *r, int file, int ptr, int dir) {
  (void)r;
  (void)file;
  (void)ptr;
  (void)dir;

  return 0;
}

/***************************************************************************/

__attribute__((used))
int _fstat_r(struct _reent *r, int file, struct stat * st) {
  (void)r;
  (void)file;

  memset(st, 0, sizeof(*st));
  st->st_mode = S_IFCHR;
  return 0;
}

/***************************************************************************/

__attribute__((used))
int _isatty_r(struct _reent *r, int fd) {
  (void)r;
  (void)fd;

  return 1;
}

/***************************************************************************/

__attribute__((used))
caddr_t _sbrk_r(struct _reent *r, int incr) {
#if CH_CFG_USE_MEMCORE
  void *p;

  chDbgCheck(incr >= 0);

  p = chCoreAllocFromBase((size_t)incr, 1U, 0U);
  if (p == NULL) {
    __errno_r(r)  = ENOMEM;
    return (caddr_t)-1;
  }
  return (caddr_t)p;
#else
  (void)incr;
  __errno_r(r) = ENOMEM;
  return (caddr_t)-1;
#endif
}

/***************************************************************************/

__attribute__((used))
void _exit(int status) {

  (void) status;

  chSysHalt("exit");
  abort();
}

/***************************************************************************/

__attribute__((used))
int _kill(int pid, int sig) {

  (void) pid;
  (void) sig;

  chSysHalt("kill");
  abort();
}

/***************************************************************************/

__attribute__((used))
int _getpid(void) {

  return 1;
  abort();
}

#ifdef __cplusplus
extern "C" {
  void __cxa_pure_virtual(void) {
    osalSysHalt("pure virtual");
  }
}
#endif
/*** EOF ***/
