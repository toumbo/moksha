#ifdef E_TYPEDEFS

typedef struct _E_Gadcon_Popup E_Gadcon_Popup;

#else
#ifndef E_GADCON_POPUP_H
#define E_GADCON_POPUP_H

#define E_GADCON_POPUP_TYPE 0xE0b0104e

struct _E_Gadcon_Popup
{
   E_Object             e_obj_inherit;

   E_Popup	       *win;
   E_Gadcon_Client     *gcc;
   Evas_Coord		w, h;
   Evas_Object	       *o_bg;

   Eina_Bool            pinned E_BITFIELD;
   Eina_Bool            gadcon_lock E_BITFIELD;
   Eina_Bool            gadcon_was_locked E_BITFIELD;
};

EAPI E_Gadcon_Popup *e_gadcon_popup_new(E_Gadcon_Client *gcc);
EAPI void e_gadcon_popup_content_set(E_Gadcon_Popup *pop, Evas_Object *o);
EAPI void e_gadcon_popup_show(E_Gadcon_Popup *pop);
EAPI void e_gadcon_popup_hide(E_Gadcon_Popup *pop);
EAPI void e_gadcon_popup_toggle_pinned(E_Gadcon_Popup *pop);
EAPI void e_gadcon_popup_lock_set(E_Gadcon_Popup *pop, Eina_Bool setting);

#endif
#endif
