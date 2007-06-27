/**
 * @file thexpmap.h
 * Export class.
 */
  
/* Copyright (C) 2000 Stacho Mudrak
 * 
 * $Date: $
 * $RCSfile: $
 * $Revision: $
 *
 * -------------------------------------------------------------------- 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * --------------------------------------------------------------------
 */
 
#ifndef thexpmap_h
#define thexpmap_h


#include "thexport.h"
#include "thsymbolset.h"
#include "thlayout.h"
#include "thlang.h"

/**
 * map export options.
 */

enum {
  TT_EXPMAP_OPT_UNKNOWN = 0,  ///< Unknown option
  TT_EXPMAP_OPT_FORMAT,  ///< Output option.
  TT_EXPMAP_OPT_PROJECTION,  ///< Output projection.
  TT_EXPMAP_OPT_LAYOUT,  ///< Layout.
  TT_EXPMAP_OPT_ENCODING,  ///< Output encoding.
};


/**
 * Options parsing table.
 */
 
static const thstok thtt_expmap_opt[] = {
  {"-enc", TT_EXPMAP_OPT_ENCODING},
  {"-encoding", TT_EXPMAP_OPT_ENCODING},
  {"-fmt", TT_EXPMAP_OPT_FORMAT},
  {"-format", TT_EXPMAP_OPT_FORMAT},
  {"-layout", TT_EXPMAP_OPT_LAYOUT},
  {"-proj", TT_EXPMAP_OPT_PROJECTION},
  {"-projection", TT_EXPMAP_OPT_PROJECTION},
  {NULL, TT_EXPMAP_OPT_UNKNOWN}
};



/**
 * map export formats.
 */

enum {
  TT_EXPMAP_FMT_UNKNOWN = 0,  ///< Unknown option
  TT_EXPMAP_FMT_SVG,  
  TT_EXPMAP_FMT_XHTML,
  TT_EXPMAP_FMT_PDF, 
  TT_EXPMAP_FMT_XVI,  
  TT_EXPMAP_FMT_3D,  
  TT_EXPMAP_FMT_SHP,  
  TT_EXPMAP_FMT_KML,  
  TT_EXPMAP_FMT_DXF,  
};


/**
 * Format parsing table.
 */
 
static const thstok thtt_expmap_fmt[] = {
  {"dxf", TT_EXPMAP_FMT_DXF},
  {"esri", TT_EXPMAP_FMT_SHP},
  {"kml", TT_EXPMAP_FMT_KML},
  {"pdf", TT_EXPMAP_FMT_PDF},
  {"shapefile", TT_EXPMAP_FMT_SHP},
  {"shapefiles", TT_EXPMAP_FMT_SHP},
  {"shp", TT_EXPMAP_FMT_SHP},
  {"survex", TT_EXPMAP_FMT_3D},
  {"svg", TT_EXPMAP_FMT_SVG},
  {"xhtml", TT_EXPMAP_FMT_XHTML},
  {"xvi", TT_EXPMAP_FMT_XVI},
  {NULL, TT_EXPMAP_FMT_UNKNOWN}
};



/**
 * Scrap mp export struct.
 */

class thexpmapmpxs {

  public:
  
  FILE * file; ///< output file
  class thdb2dprj * proj;
  double ms, mx, my, sr, cr, rr; ///< Scale and centering.

  thsymbolset * symset;
  thlayout * layout;
  char * attr_last_id, * attr_last_survey, * attr_last_scrap;
  bool attr_last_scrap_centerline;

  double m_shift_x, m_shift_y;
  
  thexpmapmpxs() : file(NULL), proj(NULL), ms(1.0), mx(0.0), my(0.0), sr(0.0), cr(1.0), rr(0.0),
    attr_last_id(""), attr_last_survey(""), attr_last_scrap(""), attr_last_scrap_centerline(false),
    m_shift_x(0.0), m_shift_y(0.0) {}
  
};


#define thxmmxst(out, sx, sy) \
  (((sx) - (out)->mx) * (out)->cr + \
   ((sy) - (out)->my) * (out)->sr) * out->ms, \
  (((sy) - (out)->my) * (out)->cr - \
   ((sx) - (out)->mx) * (out)->sr) * out->ms 

enum {
  TT_XMPS_NONE = 0,
  TT_XMPS_COUNT = 5,
  TT_XMPS_F = 1,
  TT_XMPS_COUNT_F = 0,
  TT_XMPS_B = 2,
  TT_XMPS_COUNT_B = 1,
  TT_XMPS_E = 4,
  TT_XMPS_COUNT_E = 2,
  TT_XMPS_X = 8,
  TT_XMPS_COUNT_X = 3,
};


struct thexpmap_xmps {
  int flags;
  long F,B,E,X;
  thexpmap_xmps() : flags(TT_XMPS_NONE), F(-1), B(-1), E(-1), X(-1) {}
};


/**
 * Main export class.
 */
 
class thexpmap : public thexport {


  public:
  
  friend class thexporter;
  
  int format,  ///< Output format.
    encoding;  ///< Output encoding.
  char * projstr,  ///< Projection string.
    * layoutstr;  ///< Layout string.
  class thdb2dprj * projptr;  ///< Projection pointer.
  class thlayout * layout;  ///< Layout pointer.
  thsymbolset symset;
  
  thbuffer layoutopts;  ///< Layout options buffer.

  void export_xvi(class thdb2dprj * prj);
  
  void export_pdf(class thdb2dxm * maps, class thdb2dprj * prj);
  thexpmap_xmps export_mp(thexpmapmpxs * out, class thscrap * scrap, unsigned & startnum, bool outline_mode);  
	void export_pdf_set_colors(class thdb2dxm * maps, class thdb2dprj * prj);

  void export_uni(class thdb2dxm * maps, class thdb2dprj * prj);
  void export_uni_scrap(FILE * out, class thscrap * scrap);  

  void export_shp(class thdb2dxm * maps, class thdb2dprj * prj);
  void export_kml(class thdb2dxm * maps, class thdb2dprj * prj);
  void export_dxf(class thdb2dxm * maps, class thdb2dprj * prj);

  public:
  
  thexpmap(); ///< Default constructor.

  virtual ~thexpmap(); ///< Default destructor.

  /**
   * Parse map export options.
   */
   
  virtual void parse_options(int & argx, int nargs, char ** args);

  /**
   * Parse layout options.
   */
   
  void parse_layout_option(int & argx, int nargs, char ** args);

  
  /**
   * Dump object into file.
   */
   
  virtual void dump_body(FILE * xf);


  /**
   * Dump object into file.
   */
   
  virtual void dump_header(FILE * xf);
  

  /**
   * Make export.
   */
   
  virtual void process_db(class thdatabase * dbp);


  /**
   * Parse export projection.
   */
   
  void parse_projection(class thdatabase * dbp);  
  
};


/**
 * Quick map export scale.
 */
 
extern double thexpmap_quick_map_export_scale;

void thexpmap_log_log_file(char * logfpath, char * on_title, char * off_title, bool mpbug = false);

#endif

