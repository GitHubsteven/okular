
#ifndef _DVIFILE_H
#define _DVIFILE_H

#include <stdio.h>
#include <qdatastream.h>
#include <qfile.h>
#include <qstring.h>

#include "bigEndianByteReader.h"

class fontPool;

class dvifile : public bigEndianByteReader
{
 public:
  dvifile(QString fname, class fontPool *pool);
  ~dvifile();

  fontPool     * font_pool;
  QString        filename;
  QString        generatorString;
  Q_UINT16       total_pages;
  Q_UINT32     * page_offset;

  Q_UINT8      * dvi_Data;
  QIODevice::Offset size_of_file;
  QString        errorMsg;

  /** This flag is set to "true" during the construction of the
      dvifile, and is never changed afterwards by the dvifile
      class. It is used in kdvi in conjuction with source-specials:
      the first time a page with source specials is rendered, KDVI
      shows an info dialog, and the flag is set to false. That way
      KDVI ensures that the user is only informed once. */
  bool           sourceSpecialMarker;

  /** Numerator and denominator of the TeX units, as explained in
      section A.3 of the DVI driver standard, Level 0, published by
      the TUG DVI driver standards committee. */
  Q_UINT32       numerator, denominator;

  /** Magnification value, as explained in section A.3 of the DVI
      driver standard, Level 0, published by the TUG DVI driver
      standards committee. */
  Q_UINT32       magnification;

  /** dimconv = numerator*magnification/(1000*denominator), as
      explained in section A.3 of the DVI driver standard, Level 0,
      published by the TUG DVI driver standards committee. */
  double         dimconv;

 private:
  /** process_preamble reads the information in the preamble and
      stores it into global variables for later use. */
  /** read_postamble reads the information in the postamble, storing
      it into global variables. It also takes care of reading in all
      of the pixel files for the fonts used in the job. */
  void           process_preamble(void);
  void           find_postamble(void);
  void           read_postamble(void);
  void           prepare_pages(void);

  /** Offset in DVI file of last page, set in read_postamble(). */
  Q_UINT32       last_page_offset;
  Q_UINT32       beginning_of_postamble;
};

#endif //ifndef _DVIFILE_H
