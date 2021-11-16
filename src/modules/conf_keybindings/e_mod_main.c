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
   //~ Eina_List *l = NULL;
   //~ E_Config_Binding_Key *bi;
   Evas_Object *o, *ob, *ot;
   Evas_Coord mw, mh;
   Evas_Coord sw, sh;
   
   if (dia) e_util_defer_object_del(E_OBJECT(dia)); 
   
   dia = e_dialog_new(e_container_current_get(e_manager_current_get()),
                      "E", "_show_keybindings");
   if (!dia) return;
   e_dialog_title_set(dia, _("Help: key bindings"));
   e_dialog_button_add(dia, _("OK"), NULL, NULL, NULL);
   e_dialog_button_add(dia, _("Edit"), NULL, _edit_bindings, NULL);
   e_win_centered_set(dia->win, 1);
   e_dialog_resizable_set(dia, 0);
   
   o = e_widget_table_add(dia->win->evas, 0);
   
   ot = e_widget_frametable_add(o, _("WINDOWS"), 0);
   ob = e_widget_label_add(o, _(" Close window:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 0, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT X"), NULL, NULL, NULL, NULL);
   e_widget_frametable_object_append(ot, ob, 1, 0, 1, 1, 1, 0, 1, 0);

   ob = e_widget_label_add(o, _(" Iconic mode toggle:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 1, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT I"), NULL, NULL, NULL, NULL);
   e_widget_frametable_object_append(ot, ob, 1, 1, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Maximize window:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 2, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("WIN Up"), NULL, NULL, NULL, NULL);
   e_widget_frametable_object_append(ot, ob, 1, 2, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Tile Left:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 3, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("WIN Left"), NULL, NULL, NULL, NULL);
   e_widget_frametable_object_append(ot, ob, 1, 3, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Tile Right:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 4, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("WIN Right"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 4, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Next Window:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 5, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT TAB"), NULL, NULL, NULL, NULL);  
   e_widget_frametable_object_append(ot, ob, 1, 5, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Always on top:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 6, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT T"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 6, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Fullscreen mode toggle:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 7, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT F"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 7, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Kill Window:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 8, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT K"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 8, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Window menu:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 9, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT W"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 9, 1, 1, 1, 0, 1, 0);
   e_widget_table_object_append(o, ot, 0, 0, 1, 1, 1, 1, 1, 1);
   
   
   //~ ----------------------------------------------
   ot = e_widget_frametable_add(o, _("SYSTEM"), 0);
   ob = e_widget_label_add(o, _(" Lock system:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 0, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT L"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 0, 1, 1, 1, 0, 1, 0);

   ob = e_widget_label_add(o, _(" Show main menu:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 1, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT M"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 1, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Show Favorites Menu:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 2, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT Menu"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 2, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" System Controls:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 3, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT DEL"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 3, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Restart Moksha:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 4, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT END"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 4, 1, 1, 1, 0, 1, 0);
   
   e_widget_table_object_append(o, ot, 0, 1, 1, 1, 1, 1, 1, 1);
   
    //~ ----------------------------------------------
   ot = e_widget_frametable_add(o, _("DESKTOP"), 0);
  ob = e_widget_label_add(o, _(" Switch to Desktop 0:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 0, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F1"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 0, 1, 1, 1, 0, 1, 0);

   ob = e_widget_label_add(o, _(" Switch to Desktop 1:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 1, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F2"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 1, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Switch to Desktop 2:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 2, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F3"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 2, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Switch to Desktop 3:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 3, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F4"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 3, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Switch to Desktop 4:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 4, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F5"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 4, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Switch to Desktop 5:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 5, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F6"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 5, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Switch to Desktop 6:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 6, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F7"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 6, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Switch to Desktop 7:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 7, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F8"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 7, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Switch to Desktop 8:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 8, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F9"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 8, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Switch to Desktop 9:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 9, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT F10"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 9, 1, 1, 1, 0, 1, 0);
   
   //~ ob = e_widget_label_add(o, _(" Switch to Desktop 10:"));
   //~ e_widget_size_min_get(ob, &sw, &sh);
   //~ e_widget_frametable_object_append_full(ot, ob, 0, 10, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   //~ ob = e_widget_button_add(o, _("ALT F11"), NULL, NULL, NULL, NULL); 
   //~ e_widget_frametable_object_append(ot, ob, 1, 10, 1, 1, 1, 0, 1, 0);
   
   //~ ob = e_widget_label_add(o, _(" Switch to Desktop 11:"));
   //~ e_widget_size_min_get(ob, &sw, &sh);
   //~ e_widget_frametable_object_append_full(ot, ob, 0, 11, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   //~ ob = e_widget_button_add(o, _("ALT F12"), NULL, NULL, NULL, NULL); 
   //~ e_widget_frametable_object_append(ot, ob, 1, 11, 1, 1, 1, 0, 1, 0);
   
   e_widget_table_object_append(o, ot, 1, 0, 1, 1, 1, 1, 1, 1);
   
    //~ ----------------------------------------------
   ot = e_widget_frametable_add(o, _("MISCELLANEOUS"), 0);
   ob = e_widget_label_add(o, _(" Quick Launcher:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 0, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("ALT ESCAPE"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 0, 1, 1, 1, 0, 1, 0);

   ob = e_widget_label_add(o, _(" Take Screenshot:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 1, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("PrtScr"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 1, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" Show the Desktop:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 2, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("CTRL ALT D"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 2, 1, 1, 1, 0, 1, 0);
   
   ob = e_widget_label_add(o, _(" This Help:"));
   e_widget_size_min_get(ob, &sw, &sh);
   e_widget_frametable_object_append_full(ot, ob, 0, 3, 1, 1, 1, 0, 1, 0, 1.0, 0.5, sw, sh, sw, sh);
   ob = e_widget_button_add(o, _("WIN F1"), NULL, NULL, NULL, NULL); 
   e_widget_frametable_object_append(ot, ob, 1, 3, 1, 1, 1, 0, 1, 0);
   
   e_widget_table_object_append(o, ot, 1, 1, 1, 1, 1, 1, 1, 1);
   
   
   //~ int i = 1;
   //~ EINA_LIST_FOREACH(e_config->key_bindings, l, bi)
     //~ {
        //~ bi->key = eina_stringshare_add(bi->key);
        //~ bi->modifiers = bi->modifiers;
        //~ bi->params = eina_stringshare_ref(bi->params);
        //~ bi->action = eina_stringshare_ref(bi->action);
        //~ if (strcmp(bi->action, "window_raise") == 0)
          //~ e_util_dialog_internal(" ",bi->key);
        //~ switch (bi->modifiers){
          //~ case 1:
                 //~ sprintf(mod_buf, "SHIFT %s", bi->key);
                 //~ break;
          //~ case 2:
                 //~ sprintf(mod_buf, "CTRL %s", bi->key);
                 //~ break;
          //~ case 3:
                 //~ sprintf(mod_buf, "CTRL SHIFT %s", bi->key);
                 //~ break;
          //~ case 4:
                 //~ sprintf(mod_buf, "ALT %s", bi->key);
                 //~ break;
          //~ case 5:
                 //~ sprintf(mod_buf, "ALT SHIFT %s", bi->key);
                 //~ break;
          //~ case 6:
                 //~ sprintf(mod_buf, "CTRL ALT %s", bi->key);
                 //~ break;
          //~ case 8:
                 //~ sprintf(mod_buf, "WIN %s", bi->key);
                 //~ break;
        //~ }
        
        //~ if (bi->modifiers > 0)
        //~ {
          //~ const char *numb = "0";
          //~ (i > 9) ? numb++ : numb;  
          //~ sprintf(buf, "%s%d. %s\n", numb, i, mod_buf);
          //~ eina_strbuf_append(eina_buf, buf);
          //~ sprintf(buf, "%s%d. %s\n", numb, i, e_action_predef_label_get(bi->action, bi->params));
          //~ eina_strbuf_append(eina_buf2, buf);
          //~ i++;
        //~ }
      //~ }

   

   //~ e_widget_list_object_append(ol, of, 0, 0, 0.5);
   e_widget_size_min_get(o, &mw, &mh);
   e_dialog_content_set(dia, o, mw, mh);
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

