/*
    ChibiOS - Copyright (C) 2006,2007,2008,2009,2010,2011,2012,2013,2014,
              2015,2016,2017,2018,2019,2020,2021 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation version 3 of the License.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    vfs/src/chpaths.c
 * @brief   VFS path utilities code.
 *
 * @addtogroup VFS_PATHS
 * @{
 */

#include "vfs.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Appends a path to a path.
 *
 * @param[out] dst              The destination buffer.
 * @param[in] src               The source path.
 * @param[in[ size              Destination buffer size.
 * @return                      The operation status.
 * @retval VFS_RET_ENAMETOOLONG If the path size exceeded the buffer size.
 */
msg_t vfs_path_append(char *dst, const char *src, size_t size) {
  size_t n;

  /* Current path length.*/
  n = strnlen(dst, size);
  if (n >= size) {
    return VFS_RET_ENAMETOOLONG;
  }

  /* Making sure to start with a separator in place.*/
  if (n == 0U) {
    *dst++ = '/';
    n++;
  }
  else {
    dst = dst + n;
    if (*(dst - 1) != '/') {
      *dst++ = '/';
      n++;
    }
  }

  /* The appended part needs to not begin with a separator.*/
  if (*src == '/') {
    src++;
  }

  /* Appending.*/
  while ((*dst++ = *src++) != '\0') {
    n++;

    if (n > size) {
      return VFS_RET_ENAMETOOLONG;
    }
  }

  *dst = '\0';

  return VFS_RET_SUCCESS;
}

/**
 * @brief   Normalizes an absolute path.
 *
 * @param[out] dst              The destination buffer.
 * @param[in] src               The source path.
 * @param[in[ size              Destination buffer size.
 * @return                      The operation status.
 * @retval VFS_RET_ENAMETOOLONG If the path size exceeded the buffer size.
 */
msg_t vfs_path_normalize(char *dst, const char *src, size_t size) {
  size_t n;

  VFS_RETURN_ON_ERROR(vfs_parse_match_separator(&src));

  *dst++ = '/';
  n = 1U;
  while (true) {
    msg_t ret;

    /* Consecutive input separators are consumed.*/
    while (vfs_parse_is_separator(*src)) {
      src++;
    }

    /* Getting next element from the input path and copying it to
       the output path.*/
    ret = vfs_parse_get_fname(&src, dst, size - n);
    VFS_RETURN_ON_ERROR(ret);

    if ((size_t)ret == 0U) {

      /* If the path contains something after the root separator.*/
      if (n > 1U) {
        /* No next path element, replacing the last separator with a zero.*/
        n--;
        *(dst - 1) = '\0';
      }

      return (msg_t)n;
    }

    /* Handling special cases of "." and "..".*/
    if (strcmp(dst, ".") == 0) {
      /* Single dot elements are discarded.*/
      /* Consecutive input separators are consumed.*/
      continue;
    }
    else if (strcmp(dst, "..") == 0) {
      /* Double dot elements require to remove the last element from
         the output path.*/
      if (n > 1U) {
        /* Back on the separator.*/
        dst--;
        n--;

        /* Scanning back to just after the previous separator.*/
        do {
          dst--;
          n--;
        } while(!vfs_parse_is_separator(*(dst - 1)));
      }
      continue;
    }

    dst += (size_t)ret;
    n   += (size_t)ret;

    /* Adding a single separator to the output.*/
    *dst++ = '/';
    n++;
  }
}

/** @} */
