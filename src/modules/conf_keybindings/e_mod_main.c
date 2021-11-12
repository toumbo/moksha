#include "e.h"
#include "e_mod_main.h"

/* actual module specifics */
static E_Module *conf_module = NULL;
static E_Action *act = NULL;
static E_Dialog *dia;

/* module setup */
EAPI E_Module_Api e_modapi =
{
   E_MODULE_API_VERSION,
   "Settings - Input Controls"
};

static void
_edit_bindings()
{
  E_Container *con;

  con = e_container_current_get(e_manager_current_get());
  e_int_config_keybindings(con, NULL);
  
  if (dia) e_util_defer_object_del(E_OBJECT(dia));
}

static void
_show_keybidings_cb()
{
   Eina_List *l = NULL;
   E_Config_Binding_Key *bi, *bi2;
   
   Evas_Object *o, *of, *ob, *ol;
   Evas_Coord mw, mh;
   if (dia) e_util_defer_object_del(E_OBJECT(dia)); 
   
   dia = e_dialog_new(e_container_current_get(e_manager_current_get()),
                      "E", "_show_keybindings");
   if (!dia) return;
   e_dialog_title_set(dia, _("Help: key bindings"));
   e_dialog_button_add(dia, _("OK"), NULL, NULL, NULL);
   e_dialog_button_add(dia, _("Edit"), NULL, _edit_bindings, NULL);
   e_win_centered_set(dia->win, 1);
   e_dialog_resizable_set(dia, 0);
   
   o = dia->win->evas;
   
   ol = e_widget_list_add(o, 0, 0);
   of = e_widget_framelist_add(o, _("The current key bindings"), 0);
   ob = e_widget_ilist_add(of, 32 * e_scale, 32 * e_scale, NULL);
   e_widget_size_min_set(ob, 300 * e_scale, 260 * e_scale);
  
   EINA_LIST_FOREACH(e_config->key_bindings, l, bi)
     {
        char mod_buf[64];
        char buf[PATH_MAX];
        if (!bi) continue;

        bi2 = E_NEW(E_Config_Binding_Key, 1);
        bi2->key = eina_stringshare_add(bi->key);
        bi2->modifiers = bi->modifiers;
        bi2->params = eina_stringshare_ref(bi->params);
        bi2->action = eina_stringshare_ref(bi->action);
         
        switch (bi2->modifiers){
          case 1:
                 sprintf(mod_buf, "SHIFT %s", bi2->key);
                 break;
          case 2:
                 sprintf(mod_buf, "CTRL %s", bi2->key);
                 break;
          case 3:
                 sprintf(mod_buf, "CTRL SHIFT %s", bi2->key);
                 break;
          case 4:
                 sprintf(mod_buf, "ALT %s", bi2->key);
                 break;
          case 5:
                 sprintf(mod_buf, "ALT SHIFT %s", bi2->key);
                 break;
          case 6:
                 sprintf(mod_buf, "CTRL ALT %s", bi2->key);
                 break;
          case 8:
                 sprintf(mod_buf, "WIN %s", bi2->key);
                 break;
        }
        
        if (bi2->modifiers > 0)
        {
          e_widget_ilist_header_append(ob, NULL, mod_buf);
          sprintf(buf, "%s", e_action_predef_label_get(bi2->action, bi2->params));
          e_widget_ilist_append(ob, NULL, buf, NULL, NULL, NULL);
        }
      }
      
   e_widget_framelist_object_append(of, ob);
   e_widget_list_object_append(ol, of, 0, 0, 0.5);
   e_widget_size_min_get(ol, &mw, &mh);
   e_dialog_content_set(dia, ol, mw, mh);
   e_dialog_show(dia);
    
      
}

EAPI void *
e_modapi_init(E_Module *m)
{
   e_configure_registry_category_add("keyboard_and_mouse", 40, _("Input"),
                                     NULL, "preferences-behavior");

   e_configure_registry_item_add("keyboard_and_mouse/key_bindings", 10,
                                 _("Key Bindings"), NULL,
                                 "preferences-desktop-keyboard-shortcuts",
                                 e_int_config_keybindings);
   e_configure_registry_item_add("keyboard_and_mouse/mouse_bindings", 20,
                                 _("Mouse Bindings"), NULL,
                                 "preferences-desktop-mouse",
                                 e_int_config_mousebindings);
   e_configure_registry_item_add("keyboard_and_mouse/acpi_bindings", 30,
                                 _("ACPI Bindings"), NULL,
                                 "preferences-system-power-management",
                                 e_int_config_acpibindings);
                                 
   act = e_action_add("show_keybinds");
   if (act)
     {
        act->func.go = _show_keybidings_cb;
        e_action_predef_name_set(_("Help"), _("The current keybindings"),
                                 "show_keybinds", NULL, NULL, 0);
     }
   conf_module = m;
   e_module_delayed_set(m, 1);
   return m;
}

EAPI int
e_modapi_shutdown(E_Module *m __UNUSED__)
{
   E_Config_Dialog *cfd;

   while ((cfd = e_config_dialog_get("E", "keyboard_and_mouse/acpi_bindings")))
     e_object_del(E_OBJECT(cfd));
   while ((cfd = e_config_dialog_get("E", "keyboard_and_mouse/mouse_bindings")))
     e_object_del(E_OBJECT(cfd));
   while ((cfd = e_config_dialog_get("E", "keyboard_and_mouse/key_bindings")))
     e_object_del(E_OBJECT(cfd));

   e_configure_registry_item_del("keyboard_and_mouse/acpi_bindings");
   e_configure_registry_item_del("keyboard_and_mouse/mouse_bindings");
   e_configure_registry_item_del("keyboard_and_mouse/key_bindings");

   e_configure_registry_category_del("keyboard_and_mouse");
   
   if (act)
     {
        e_action_predef_name_del("Help", "Show current key binds");
        e_action_del("show_keybinds");
        act = NULL;
     }
   
   conf_module = NULL;
   return 1;
}

EAPI int
e_modapi_save(E_Module *m __UNUSED__)
{
   return 1;
}

