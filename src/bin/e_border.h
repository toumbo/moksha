#ifdef E_TYPEDEFS

typedef enum _E_Screen_Limits
{
    E_SCREEN_LIMITS_PARTLY = 0,
    E_SCREEN_LIMITS_COMPLETELY = 1,
    E_SCREEN_LIMITS_WITHIN = 2
} E_Screen_Limits;

typedef enum _E_Icon_Preference
{
   E_ICON_PREF_E_DEFAULT,
   E_ICON_PREF_NETWM,
   E_ICON_PREF_USER
} E_Icon_Preference;

typedef enum _E_Direction
{
   E_DIRECTION_UP,
   E_DIRECTION_DOWN,
   E_DIRECTION_LEFT,
   E_DIRECTION_RIGHT
} E_Direction;

typedef enum _E_Transition
{
   E_TRANSITION_LINEAR = 0,
   E_TRANSITION_SINUSOIDAL = 1,
   E_TRANSITION_ACCELERATE = 2,
   E_TRANSITION_DECELERATE = 3,
   E_TRANSITION_ACCELERATE_LOTS = 4,
   E_TRANSITION_DECELERATE_LOTS = 5,
   E_TRANSITION_SINUSOIDAL_LOTS = 6,
   E_TRANSITION_BOUNCE = 7,
   E_TRANSITION_BOUNCE_LOTS = 8
} E_Transition;

typedef enum _E_Stacking
{
   E_STACKING_NONE,
   E_STACKING_ABOVE,
   E_STACKING_BELOW
} E_Stacking;

typedef enum _E_Focus_Policy
{
   E_FOCUS_CLICK,
   E_FOCUS_MOUSE,
   E_FOCUS_SLOPPY,
   E_FOCUS_LAST
} E_Focus_Policy;

typedef enum _E_Urgency_Policy
{
   E_ACTIVEHINT_POLICY_IGNORE,
   E_ACTIVEHINT_POLICY_ANIMATE,
   E_ACTIVEHINT_POLICY_ACTIVATE
} E_Urgency_Policy;

typedef enum _E_Focus_Setting
{
   E_FOCUS_NONE,
   E_FOCUS_NEW_WINDOW,
   E_FOCUS_NEW_DIALOG,
   E_FOCUS_NEW_DIALOG_IF_OWNER_FOCUSED
} E_Focus_Setting;

typedef enum _E_Maximize
{
   E_MAXIMIZE_NONE = 0x00000000,
   E_MAXIMIZE_FULLSCREEN = 0x00000001,
   E_MAXIMIZE_SMART = 0x00000002,
   E_MAXIMIZE_EXPAND = 0x00000003,
   E_MAXIMIZE_FILL = 0x00000004,
   E_MAXIMIZE_TYPE = 0x0000000f,
   E_MAXIMIZE_VERTICAL = 0x00000010,
   E_MAXIMIZE_HORIZONTAL = 0x00000020,
   E_MAXIMIZE_BOTH = 0x00000030,
   E_MAXIMIZE_LEFT = 0x00000070,
   E_MAXIMIZE_RIGHT = 0x000000b0,
   E_MAXIMIZE_DIRECTION = 0x000000f0
} E_Maximize;

typedef enum _E_Fullscreen
{
   /* Resize window */
   E_FULLSCREEN_RESIZE,
   /* Change screen resoultion and resize window */
   E_FULLSCREEN_ZOOM
} E_Fullscreen;

typedef enum _E_Window_Placement
{
   E_WINDOW_PLACEMENT_SMART,
   E_WINDOW_PLACEMENT_ANTIGADGET,
   E_WINDOW_PLACEMENT_CURSOR,
   E_WINDOW_PLACEMENT_MANUAL
} E_Window_Placement;

typedef enum _E_Border_Hook_Point
{
   E_BORDER_HOOK_EVAL_PRE_FETCH,
   E_BORDER_HOOK_EVAL_PRE_POST_FETCH,
   E_BORDER_HOOK_EVAL_POST_FETCH,
   E_BORDER_HOOK_EVAL_PRE_BORDER_ASSIGN,
   E_BORDER_HOOK_EVAL_POST_BORDER_ASSIGN,
   E_BORDER_HOOK_EVAL_PRE_NEW_BORDER,
   E_BORDER_HOOK_EVAL_POST_NEW_BORDER,
   E_BORDER_HOOK_EVAL_END,
   E_BORDER_HOOK_CONTAINER_LAYOUT,
   E_BORDER_HOOK_NEW_BORDER,
   E_BORDER_HOOK_SET_DESK,
   E_BORDER_HOOK_MOVE_BEGIN,
   E_BORDER_HOOK_MOVE_UPDATE,
   E_BORDER_HOOK_MOVE_END,
   E_BORDER_HOOK_RESIZE_BEGIN,
   E_BORDER_HOOK_RESIZE_UPDATE,
   E_BORDER_HOOK_RESIZE_END
} E_Border_Hook_Point;

typedef struct _E_Border                     E_Border;
typedef struct _E_Border_Pending_Move_Resize E_Border_Pending_Move_Resize;
typedef struct _E_Border_Hook                E_Border_Hook;
typedef struct _E_Event_Border_Simple        E_Event_Border_Resize;
typedef struct _E_Event_Border_Simple        E_Event_Border_Move;
typedef struct _E_Event_Border_Simple        E_Event_Border_Add;
typedef struct _E_Event_Border_Simple        E_Event_Border_Remove;
typedef struct _E_Event_Border_Simple        E_Event_Border_Show;
typedef struct _E_Event_Border_Simple        E_Event_Border_Hide;
typedef struct _E_Event_Border_Simple        E_Event_Border_Iconify;
typedef struct _E_Event_Border_Simple        E_Event_Border_Uniconify;
typedef struct _E_Event_Border_Simple        E_Event_Border_Stick;
typedef struct _E_Event_Border_Simple        E_Event_Border_Unstick;
typedef struct _E_Event_Border_Zone_Set      E_Event_Border_Zone_Set;
typedef struct _E_Event_Border_Desk_Set      E_Event_Border_Desk_Set;
typedef struct _E_Event_Border_Stack         E_Event_Border_Stack;
typedef struct _E_Event_Border_Simple        E_Event_Border_Icon_Change;
typedef struct _E_Event_Border_Simple        E_Event_Border_Urgent_Change;
typedef struct _E_Event_Border_Simple        E_Event_Border_Focus_In;
typedef struct _E_Event_Border_Simple        E_Event_Border_Focus_Out;
typedef struct _E_Event_Border_Simple        E_Event_Border_Property;
typedef struct _E_Event_Border_Simple        E_Event_Border_Fullscreen;
typedef struct _E_Event_Border_Simple        E_Event_Border_Unfullscreen;
typedef void                               (*E_Border_Move_Intercept_Cb)(E_Border *, int x, int y);
#else
#ifndef E_BORDER_H
#define E_BORDER_H

#define E_BORDER_TYPE (int)0xE0b01002

struct _E_Border
{
   E_Object e_obj_inherit;

   struct
   {
      struct
      {
         int x, y, w, h;
         int mx, my;
      } current, last_down[3], last_up[3];
   } mouse;

   struct
   {
      struct
      {
         int x, y, w, h;
         int mx, my;
         int button;
      } down;
   } moveinfo;

   Ecore_X_Window win;
   int            x, y, w, h;
   int            ref;
   E_Zone        *zone;
   E_Desk        *desk;
   Eina_List     *handlers;

   struct
   {
      int x, y;
      struct
      {
         int    x, y;
         double t;
      } start;
   } fx;

   struct
   {
      int l, r, t, b;
   } client_inset;

   Ecore_Evas    *bg_ecore_evas;
   Evas          *bg_evas;
   Ecore_X_Window bg_win;
   Evas_Object   *bg_object;
   Evas_Object   *icon_object;
   Ecore_X_Window event_win;
   const char    *internal_icon;
   const char    *internal_icon_key;
   Eina_Bool      bg_evas_in E_BITFIELD;

   struct
   {
      Ecore_X_Window shell_win;
      Ecore_X_Window lock_win;
      Ecore_X_Window win;

      int            x, y, w, h;

      struct
      {
         unsigned char changed E_BITFIELD;
         unsigned char user_selected E_BITFIELD;
         const char   *name;
      } border;

      unsigned char  shaped E_BITFIELD;
      unsigned char  argb E_BITFIELD;

      /* ICCCM */
      struct
      {
         const char               *title;
         const char               *name;
         const char               *class;
         const char               *icon_name;
         const char               *machine;
         int                       min_w, min_h;
         int                       max_w, max_h;
         int                       base_w, base_h;
         int                       step_w, step_h;
         int                       start_x, start_y;
         double                    min_aspect, max_aspect;
         Ecore_X_Window_State_Hint initial_state;
         Ecore_X_Window_State_Hint state;
         Ecore_X_Pixmap            icon_pixmap;
         Ecore_X_Pixmap            icon_mask;
         Ecore_X_Window            icon_window;
         Ecore_X_Window            window_group;
         Ecore_X_Window            transient_for;
         Ecore_X_Window            client_leader;
         Ecore_X_Gravity           gravity;
         const char               *window_role;
         unsigned char             take_focus E_BITFIELD;
         unsigned char             accepts_focus E_BITFIELD;
         unsigned char             urgent E_BITFIELD;
         unsigned char             delete_request E_BITFIELD;
         unsigned char             request_pos E_BITFIELD;
         struct
         {
            int    argc;
            char **argv;
         } command;
         struct
         {
            unsigned char title E_BITFIELD;
            unsigned char name_class E_BITFIELD;
            unsigned char icon_name E_BITFIELD;
            unsigned char machine E_BITFIELD;
            unsigned char hints E_BITFIELD;
            unsigned char size_pos_hints E_BITFIELD;
            unsigned char protocol E_BITFIELD;
            unsigned char transient_for E_BITFIELD;
            unsigned char client_leader E_BITFIELD;
            unsigned char window_role E_BITFIELD;
            unsigned char state E_BITFIELD;
            unsigned char command E_BITFIELD;
         } fetch;
      } icccm;

      /* MWM */
      struct
      {
         Ecore_X_MWM_Hint_Func  func;
         Ecore_X_MWM_Hint_Decor decor;
         Ecore_X_MWM_Hint_Input input;
         unsigned char          exists E_BITFIELD;
         unsigned char          borderless E_BITFIELD;
         struct
         {
            unsigned char hints E_BITFIELD;
         } fetch;
      } mwm;

      /* NetWM */
      struct
      {
         pid_t         pid;
         unsigned int  desktop;
         const char   *name;
         const char   *icon_name;
         Ecore_X_Icon *icons;
         int           num_icons;
         unsigned int  user_time;
         struct
         {
            int left;
            int right;
            int top;
            int bottom;
            int left_start_y;
            int left_end_y;
            int right_start_y;
            int right_end_y;
            int top_start_x;
            int top_end_x;
            int bottom_start_x;
            int bottom_end_x;
         } strut;
         unsigned char ping E_BITFIELD;
         struct
         {
            unsigned char        request E_BITFIELD;
            unsigned int         wait;
            Ecore_X_Sync_Alarm   alarm;
            Ecore_X_Sync_Counter counter;
            unsigned int         serial;
            double               send_time;
         } sync;

         /* NetWM Window state */
         struct
         {
            unsigned char modal E_BITFIELD;
            unsigned char sticky E_BITFIELD;
            unsigned char maximized_v E_BITFIELD;
            unsigned char maximized_h E_BITFIELD;
            unsigned char shaded E_BITFIELD;
            unsigned char skip_taskbar E_BITFIELD;
            unsigned char skip_pager E_BITFIELD;
            unsigned char hidden E_BITFIELD;
            unsigned char fullscreen E_BITFIELD;
            E_Stacking    stacking;
         } state;

         /* NetWM Window allowed actions */
         struct
         {
            unsigned char move E_BITFIELD;
            unsigned char resize E_BITFIELD;
            unsigned char minimize E_BITFIELD;
            unsigned char shade E_BITFIELD;
            unsigned char stick E_BITFIELD;
            unsigned char maximized_h E_BITFIELD;
            unsigned char maximized_v E_BITFIELD;
            unsigned char fullscreen E_BITFIELD;
            unsigned char change_desktop E_BITFIELD;
            unsigned char close E_BITFIELD;
         } action;

         Ecore_X_Window_Type  type;
         Ecore_X_Window_Type *extra_types;
         int                  extra_types_num;
         int                  startup_id;

         struct
         {
            unsigned char name E_BITFIELD;
            unsigned char icon_name E_BITFIELD;
            unsigned char icon E_BITFIELD;
            unsigned char user_time E_BITFIELD;
            unsigned char strut E_BITFIELD;
            unsigned char type E_BITFIELD;
            unsigned char state E_BITFIELD;
            /* No, fetch on new_client, shouldn't be changed after map.
               unsigned char pid E_BITFIELD;
             */
            /* No, ignore this
               unsigned char desktop E_BITFIELD;
             */
         } fetch;

         struct
         {
            unsigned char state E_BITFIELD;
         } update;
      } netwm;

      /* Extra e stuff */
      struct
      {
         struct
         {
            struct
            {
               int           x, y;

               unsigned char updated E_BITFIELD;
            } video_position;
            Ecore_X_Window video_parent;
            E_Border      *video_parent_border;
            Eina_List     *video_child;
            struct
            {
               const char     *name;
               const char    **available_list;
               int             num;
               unsigned char   wait_for_done E_BITFIELD;
               unsigned char   use E_BITFIELD;
            } profile;
            unsigned char  centered E_BITFIELD;
            unsigned char  video E_BITFIELD;
         } state;

         struct
         {
            unsigned char state E_BITFIELD;
            unsigned char video_parent E_BITFIELD;
            unsigned char video_position E_BITFIELD;
            unsigned char profile E_BITFIELD;
         } fetch;
      } e;

      struct
      {
         struct
         {
            unsigned char soft_menu E_BITFIELD;
            unsigned char soft_menus E_BITFIELD;
         } fetch;

         unsigned char soft_menu E_BITFIELD;
         unsigned char soft_menus E_BITFIELD;
      } qtopia;

      struct
      {
         struct
         {
            unsigned char state E_BITFIELD;
            unsigned char vkbd E_BITFIELD;
         } fetch;
         Ecore_X_Virtual_Keyboard_State state;
         unsigned char                  have_property E_BITFIELD;
         unsigned char                  vkbd E_BITFIELD;
      } vkbd;

      struct
      {
         struct
         {
            struct
            {
               unsigned char conformant E_BITFIELD;
            } fetch;
            unsigned char conformant E_BITFIELD;
         } conformant;
         struct
         {
            struct
            {
               unsigned char state E_BITFIELD;
               struct
               {
                  unsigned int major E_BITFIELD;
                  unsigned int minor E_BITFIELD;
               } priority;
               unsigned char quickpanel E_BITFIELD;
               unsigned char zone E_BITFIELD;
            } fetch;
            Ecore_X_Illume_Quickpanel_State state;
            struct
            {
               unsigned int major E_BITFIELD;
               unsigned int minor E_BITFIELD;
            } priority;
            unsigned char                   quickpanel E_BITFIELD;
            int                             zone;
         } quickpanel;
         struct
         {
            struct
            {
               unsigned char drag E_BITFIELD;
               unsigned char locked E_BITFIELD;
            } fetch;
            unsigned char drag E_BITFIELD;
            unsigned char locked E_BITFIELD;
         } drag;
         struct
         {
            struct
            {
               unsigned char state E_BITFIELD;
            } fetch;
            Ecore_X_Illume_Window_State state;
         } win_state;
      } illume;

      Ecore_X_Window_Attributes initial_attributes;
   } client;

   E_Container_Shape *shape;

   unsigned int       visible E_BITFIELD;
   Eina_Bool          hidden E_BITFIELD; // set when window has been hidden by api and should not be shown
   unsigned int       await_hide_event;
   unsigned int       moving E_BITFIELD;
   unsigned int       focused E_BITFIELD;
   unsigned int       new_client E_BITFIELD;
   unsigned int       re_manage E_BITFIELD;
   unsigned int       placed E_BITFIELD;
   unsigned int       shading E_BITFIELD;
   unsigned int       shaded E_BITFIELD;
   unsigned int       iconic E_BITFIELD;
   unsigned int       deskshow E_BITFIELD;
   unsigned int       sticky E_BITFIELD;
   unsigned int       shaped E_BITFIELD;
   unsigned int       shaped_input E_BITFIELD;
   unsigned int       need_shape_merge E_BITFIELD;
   unsigned int       need_shape_export E_BITFIELD;
   unsigned int       fullscreen E_BITFIELD;
   unsigned int       need_fullscreen E_BITFIELD;
   unsigned int       already_unparented E_BITFIELD;
   unsigned int       need_reparent E_BITFIELD;
   unsigned int       button_grabbed E_BITFIELD;
   unsigned int       delete_requested E_BITFIELD;
   unsigned int       ping_ok E_BITFIELD;
   unsigned int       hung E_BITFIELD;
   unsigned int       take_focus E_BITFIELD;
   unsigned int       want_focus E_BITFIELD;
   unsigned int       user_skip_winlist E_BITFIELD;
   unsigned int       need_maximize E_BITFIELD;
   E_Maximize         maximized;
   E_Fullscreen       fullscreen_policy;
   unsigned int       borderless E_BITFIELD;
   unsigned char      offer_resistance E_BITFIELD;
   const char        *bordername;

   unsigned int       lock_user_location E_BITFIELD; /*DONE*/
   unsigned int       lock_client_location E_BITFIELD; /*DONE*/
   unsigned int       lock_user_size E_BITFIELD; /*DONE*/
   unsigned int       lock_client_size E_BITFIELD; /*DONE*/
   unsigned int       lock_user_stacking E_BITFIELD; /*DONE*/
   unsigned int       lock_client_stacking E_BITFIELD; /*DONE*/
   unsigned int       lock_user_iconify E_BITFIELD; /*DONE*/
   unsigned int       lock_client_iconify E_BITFIELD; /*DONE*/
   unsigned int       lock_user_desk E_BITFIELD;
   unsigned int       lock_client_desk E_BITFIELD;
   unsigned int       lock_user_sticky E_BITFIELD; /*DONE*/
   unsigned int       lock_client_sticky E_BITFIELD; /*DONE*/
   unsigned int       lock_user_shade E_BITFIELD; /*DONE*/
   unsigned int       lock_client_shade E_BITFIELD; /*DONE*/
   unsigned int       lock_user_maximize E_BITFIELD; /*DONE*/
   unsigned int       lock_client_maximize E_BITFIELD; /*DONE*/
   unsigned int       lock_user_fullscreen E_BITFIELD; /*DONE*/
   unsigned int       lock_client_fullscreen E_BITFIELD; /*DONE*/
   unsigned int       lock_border E_BITFIELD; /*DONE*/
   unsigned int       lock_close E_BITFIELD; /*DONE*/
   unsigned int       lock_focus_in E_BITFIELD; /*DONE*/
   unsigned int       lock_focus_out E_BITFIELD; /*DONE*/
   unsigned int       lock_life E_BITFIELD; /*DONE*/

   unsigned int       internal E_BITFIELD;
   unsigned int       internal_no_remember E_BITFIELD;
   unsigned int       internal_no_reopen E_BITFIELD;
   unsigned int       stolen E_BITFIELD;

   Ecore_Evas        *internal_ecore_evas;

   double             ping;

   unsigned char      changed E_BITFIELD;

   unsigned char      icon_preference;
   unsigned char      ignore_first_unmap;
   unsigned char      resize_mode;

   struct
   {
      int          x, y, w, h;
      E_Layer      layer;
      int          zone;
      E_Maximize   maximized;
   } saved;

   struct
   {
      unsigned char valid E_BITFIELD;
      int           x, y, w, h;
      struct
      {
         int x, y, w, h;
      } saved;
   } pre_res_change;

   struct
   {
      double          start;
      double          val;
      int             x, y;
      E_Direction     dir;
      Ecore_Animator *anim;
   } shade;

   struct
   {
      int x, y;
      int modified;
   } shelf_fix;

   Eina_List       *stick_desks;
   E_Menu          *border_menu;
   E_Config_Dialog *border_locks_dialog;
   E_Config_Dialog *border_remember_dialog;
   E_Config_Dialog *border_border_dialog;
   E_Dialog        *border_prop_dialog;
   Eina_List       *pending_move_resize;

   struct
   {
      unsigned char visible E_BITFIELD;
      unsigned char pos E_BITFIELD;
      unsigned char size E_BITFIELD;
      unsigned char stack E_BITFIELD;
      unsigned char prop E_BITFIELD;
      unsigned char border E_BITFIELD;
      unsigned char reset_gravity E_BITFIELD;
      unsigned char shading E_BITFIELD;
      unsigned char shaded E_BITFIELD;
      unsigned char shape E_BITFIELD;
      unsigned char shape_input E_BITFIELD;
      unsigned char icon E_BITFIELD;
   } changes;

   struct
   {
      unsigned char start E_BITFIELD;
      int           x, y;
   } drag;

   E_Layer                    layer;
   E_Action                  *cur_mouse_action;
   Ecore_Timer               *raise_timer;
   Ecore_Poller              *ping_poller;
   Ecore_Timer               *kill_timer;
   E_Border_Move_Intercept_Cb move_intercept_cb;
   int                        shape_rects_num;
   Ecore_X_Rectangle         *shape_rects;
   E_Remember                *remember;

   E_Border                  *modal;

   E_Border                  *leader;
   Eina_List                 *group;

   E_Border                  *parent;
   Eina_List                 *transients;

   Efreet_Desktop            *desktop;
   E_Pointer                 *pointer;

   unsigned char              comp_hidden   E_BITFIELD;

   unsigned char              post_move   E_BITFIELD;
   unsigned char              post_resize E_BITFIELD;
   unsigned char              post_show E_BITFIELD;
   unsigned char              during_lost E_BITFIELD;

   Ecore_Idle_Enterer        *post_job;

   Eina_Bool                  argb;

   int                        tmp_input_hidden;
   E_Focus_Policy             focus_policy_override;
};

struct _E_Border_Pending_Move_Resize
{
   int           x, y, w, h;
   unsigned char move E_BITFIELD;
   unsigned char resize E_BITFIELD;
   unsigned char without_border E_BITFIELD;
   unsigned int  serial;
};

struct _E_Border_Hook
{
   E_Border_Hook_Point hookpoint;
   void                (*func)(void *data, void *bd);
   void               *data;
   unsigned char       delete_me E_BITFIELD;
};

struct _E_Event_Border_Simple
{
   E_Border *border;
};

struct _E_Event_Border_Zone_Set
{
   E_Border *border;
   E_Zone   *zone;
};

struct _E_Event_Border_Desk_Set
{
   E_Border *border;
   E_Desk   *desk;
};

struct _E_Event_Border_Stack
{
   E_Border  *border, *stack;
   E_Stacking type;
};

EINTERN int         e_border_init(void);
EINTERN int         e_border_shutdown(void);

EAPI E_Border      *e_border_new(E_Container *con, Ecore_X_Window win, int first_map, int internal);
EAPI void           e_border_free(E_Border *bd);
EAPI void           e_border_ref(E_Border *bd);
EAPI void           e_border_unref(E_Border *bd);
EAPI void           e_border_res_change_geometry_save(E_Border *bd);
EAPI void           e_border_res_change_geometry_restore(E_Border *bd);

EAPI void           e_border_zone_set(E_Border *bd, E_Zone *zone);
EAPI void           e_border_desk_set(E_Border *bd, E_Desk *desk);
EAPI void           e_border_show(E_Border *bd);
EAPI void           e_border_hide(E_Border *bd, int manage);
EAPI void           e_border_move(E_Border *bd, int x, int y);
EAPI void           e_border_move_intercept_cb_set(E_Border *bd, E_Border_Move_Intercept_Cb cb);
EAPI void           e_border_move_without_border(E_Border *bd, int x, int y);
EAPI void           e_border_center(E_Border *bd);
EAPI void           e_border_center_pos_get(E_Border *bd, int *x, int *y);
EAPI void           e_border_fx_offset(E_Border *bd, int x, int y);
EAPI void           e_border_resize(E_Border *bd, int w, int h);
EAPI void           e_border_resize_without_border(E_Border *bd, int w, int h);
EAPI void           e_border_move_resize(E_Border *bd, int x, int y, int w, int h);
EAPI void           e_border_move_resize_without_border(E_Border *bd, int x, int y, int w, int h);
EAPI void           e_border_layer_set(E_Border *bd, E_Layer layer);
EAPI void           e_border_raise(E_Border *bd);
EAPI void           e_border_lower(E_Border *bd);
EAPI void           e_border_stack_above(E_Border *bd, E_Border *above);
EAPI void           e_border_stack_below(E_Border *bd, E_Border *below);
EAPI void           e_border_focus_latest_set(E_Border *bd);
EAPI void           e_border_raise_latest_set(E_Border *bd);
EAPI void           e_border_focus_set_with_pointer(E_Border *bd);
EAPI void           e_border_focus_set(E_Border *bd, int focus, int set);
EAPI void           e_border_shade(E_Border *bd, E_Direction dir);
EAPI void           e_border_unshade(E_Border *bd, E_Direction dir);
EAPI void           e_border_maximize(E_Border *bd, E_Maximize max);
EAPI void           e_border_unmaximize(E_Border *bd, E_Maximize max);
EAPI void           e_border_fullscreen(E_Border *bd, E_Fullscreen policy);
EAPI void           e_border_unfullscreen(E_Border *bd);
EAPI void           e_border_iconify(E_Border *bd);
EAPI void           e_border_uniconify(E_Border *bd);
EAPI void           e_border_stick(E_Border *bd);
EAPI void           e_border_unstick(E_Border *bd);
EAPI void           e_border_pinned_set(E_Border *bd, int set);

EAPI E_Border      *e_border_find_by_client_window(Ecore_X_Window win);
EAPI E_Border      *e_border_find_all_by_client_window(Ecore_X_Window win);
EAPI E_Border      *e_border_find_by_frame_window(Ecore_X_Window win);
EAPI E_Border      *e_border_find_by_window(Ecore_X_Window win);
EAPI E_Border      *e_border_find_by_alarm(Ecore_X_Sync_Alarm alarm);
EAPI E_Border      *e_border_focused_get(void);

EAPI void           e_border_idler_before(void);

EAPI Eina_List     *e_border_client_list(void);

EAPI void           e_border_act_move_keyboard(E_Border *bd);
EAPI void           e_border_act_resize_keyboard(E_Border *bd);

EAPI void           e_border_act_move_begin(E_Border *bd, Ecore_Event_Mouse_Button *ev);
EAPI void           e_border_act_move_end(E_Border *bd, Ecore_Event_Mouse_Button *ev);
EAPI void           e_border_act_resize_begin(E_Border *bd, Ecore_Event_Mouse_Button *ev);
EAPI void           e_border_act_resize_end(E_Border *bd, Ecore_Event_Mouse_Button *ev);
EAPI void           e_border_act_menu_begin(E_Border *bd, Ecore_Event_Mouse_Button *ev, int key);
EAPI void           e_border_act_close_begin(E_Border *bd);
EAPI void           e_border_act_kill_begin(E_Border *bd);

EAPI Evas_Object   *e_border_icon_add(E_Border *bd, Evas *evas);

EAPI void           e_border_button_bindings_ungrab_all(void);
EAPI void           e_border_button_bindings_grab_all(void);

EAPI Eina_List     *e_border_focus_stack_get(void);
EAPI Eina_List     *e_border_lost_windows_get(E_Zone *zone);

EAPI void           e_border_ping(E_Border *bd);
EAPI void           e_border_move_cancel(void);
EAPI void           e_border_resize_cancel(void);
EAPI void           e_border_frame_recalc(E_Border *bd);
EAPI Eina_List     *e_border_immortal_windows_get(void);

EAPI const char    *e_border_name_get(const E_Border *bd);

EAPI void           e_border_signal_move_begin(E_Border *bd, const char *sig, const char *src);
EAPI void           e_border_signal_move_end(E_Border *bd, const char *sig, const char *src);
EAPI int            e_border_resizing_get(E_Border *bd);
EAPI void           e_border_signal_resize_begin(E_Border *bd, const char *dir, const char *sig, const char *src);
EAPI void           e_border_signal_resize_end(E_Border *bd, const char *dir, const char *sig, const char *src);
EAPI void           e_border_resize_limit(E_Border *bd, int *w, int *h);

EAPI E_Border_Hook *e_border_hook_add(E_Border_Hook_Point hookpoint, void (*func)(void *data, void *bd), void *data);
EAPI void           e_border_hook_del(E_Border_Hook *bh);
EAPI void           e_border_focus_track_freeze(void);
EAPI void           e_border_focus_track_thaw(void);

EAPI E_Border      *e_border_under_pointer_get(E_Desk *desk, E_Border *exclude);
EAPI int            e_border_pointer_warp_to_center(E_Border *bd);

EAPI void           e_border_comp_hidden_set(E_Border *bd, Eina_Bool hidden);
EAPI void           e_border_tmp_input_hidden_push(E_Border *bd);
EAPI void           e_border_tmp_input_hidden_pop(E_Border *bd);

EAPI void           e_border_activate(E_Border *bd, Eina_Bool just_do_it);

EAPI void           e_border_focus_lock_set(Eina_Bool lock);
EAPI Eina_Bool     e_border_focus_lock_get(void);

extern EAPI int E_EVENT_BORDER_RESIZE;
extern EAPI int E_EVENT_BORDER_MOVE;
extern EAPI int E_EVENT_BORDER_ADD;
extern EAPI int E_EVENT_BORDER_SHOW;
extern EAPI int E_EVENT_BORDER_HIDE;
extern EAPI int E_EVENT_BORDER_REMOVE;
extern EAPI int E_EVENT_BORDER_ICONIFY;
extern EAPI int E_EVENT_BORDER_UNICONIFY;
extern EAPI int E_EVENT_BORDER_STICK;
extern EAPI int E_EVENT_BORDER_UNSTICK;
extern EAPI int E_EVENT_BORDER_ZONE_SET;
extern EAPI int E_EVENT_BORDER_DESK_SET;
extern EAPI int E_EVENT_BORDER_STACK;
extern EAPI int E_EVENT_BORDER_ICON_CHANGE;
extern EAPI int E_EVENT_BORDER_URGENT_CHANGE;
extern EAPI int E_EVENT_BORDER_FOCUS_IN;
extern EAPI int E_EVENT_BORDER_FOCUS_OUT;
extern EAPI int E_EVENT_BORDER_PROPERTY;
extern EAPI int E_EVENT_BORDER_FULLSCREEN;
extern EAPI int E_EVENT_BORDER_UNFULLSCREEN;

/* e_config not available everywhere e_border.h is used...
static inline Eina_Bool
e_border_focus_policy_click(const E_Border *bd)
{
   return ((bd->focus_policy_override == E_FOCUS_CLICK) || (e_config->focus_policy == E_FOCUS_CLICK));
}
*/
#define e_border_focus_policy_click(bd) \
  ((bd->focus_policy_override == E_FOCUS_CLICK) || (e_config->focus_policy == E_FOCUS_CLICK))


/* macro for finding misuse of changed flag */
#if 0
# define BD_CHANGED(BD) \
  do { \
     if (e_object_is_del(E_OBJECT(BD))) \
       EINA_LOG_CRIT("CHANGED SET ON DELETED BORDER!"); \
     BD->changed = 1; \
     INF("%s:%d - BD CHANGED: %p", __FILE__, __LINE__, BD); \
  } while (0)
#else
# define BD_CHANGED(BD) BD->changed = 1
#endif

#endif
#endif
