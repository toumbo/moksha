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
   E_Config_Binding_Key *bi;
   Eina_Strbuf *eina_buf, *eina_buf2;
   Evas_Object *o, *ob, *oc, *ot;
   Evas_Coord mw, mh;
   char buf[PATH_MAX], mod_buf[64];
   
   if (dia) e_util_defer_object_del(E_OBJECT(dia)); 
   
   dia = e_dialog_new(e_container_current_get(e_manager_current_get()),
                      "E", "_show_keybindings");
   if (!dia) return;
   e_dialog_title_set(dia, _("Help: key bindings"));
   e_dialog_button_add(dia, _("OK"), NULL, NULL, NULL);
   e_dialog_button_add(dia, _("Edit"), NULL, _edit_bindings, NULL);
   e_win_centered_set(dia->win, 1);
   e_dialog_resizable_set(dia, 0);
   
   o = e_widget_list_add(dia->win->evas, 0, 0);
   
   ot = e_widget_frametable_add(o, _("The current key bindings"), 0);
   ob = e_widget_textblock_add(ot);
   e_widget_size_min_set(ob, 160 * e_scale, 480 * e_scale);
   oc = e_widget_textblock_add(ot);
   e_widget_size_min_set(oc, 200 * e_scale, 480 * e_scale);
   
   eina_buf = eina_strbuf_new();
   eina_buf2 = eina_strbuf_new();
   
   int i = 1;
   EINA_LIST_FOREACH(e_config->key_bindings, l, bi)
     {
        bi->key = eina_stringshare_add(bi->key);
        bi->modifiers = bi->modifiers;
        bi->params = eina_stringshare_ref(bi->params);
        bi->action = eina_stringshare_ref(bi->action);
        //~ if (strcmp(bi->action, "window_raise") == 0)
          //~ e_util_dialog_internal(" ",bi->key);
        switch (bi->modifiers){
          case 1:
                 sprintf(mod_buf, "SHIFT %s", bi->key);
                 break;
          case 2:
                 sprintf(mod_buf, "CTRL %s", bi->key);
                 break;
          case 3:
                 sprintf(mod_buf, "CTRL SHIFT %s", bi->key);
                 break;
          case 4:
                 sprintf(mod_buf, "ALT %s", bi->key);
                 break;
          case 5:
                 sprintf(mod_buf, "ALT SHIFT %s", bi->key);
                 break;
          case 6:
                 sprintf(mod_buf, "CTRL ALT %s", bi->key);
                 break;
          case 8:
                 sprintf(mod_buf, "WIN %s", bi->key);
                 break;
        }
        
        if (bi->modifiers > 0)
        {
          const char *numb = "0";
          (i > 9) ? numb++ : numb;  
          sprintf(buf, "%s%d. %s\n", numb, i, mod_buf);
          eina_strbuf_append(eina_buf, buf);
          sprintf(buf, "%s%d. %s\n", numb, i, e_action_predef_label_get(bi->action, bi->params));
          eina_strbuf_append(eina_buf2, buf);
          i++;
        }
      }

   e_widget_textblock_plain_set(ob, eina_strbuf_string_get(eina_buf));
   e_widget_textblock_plain_set(oc, eina_strbuf_string_get(eina_buf2));
   e_widget_frametable_object_append(ot, ob, 0, 0, 1, 1, 1, 0, 1, 0);
   e_widget_frametable_object_append(ot, oc, 1, 0, 1, 1, 1, 0, 1, 0);
   e_widget_list_object_append(o, ot, 1, 1, 0.5);

   //~ e_widget_list_object_append(ol, of, 0, 0, 0.5);
   e_widget_size_min_get(o, &mw, &mh);
   e_dialog_content_set(dia, o, mw, mh);
   eina_strbuf_free(eina_buf);
   eina_strbuf_free(eina_buf2);
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

