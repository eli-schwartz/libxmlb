/*
 * Copyright (C) 2018 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#ifndef __XB_MACHINE_H
#define __XB_MACHINE_H

G_BEGIN_DECLS

#include <glib-object.h>

#include "xb-opcode.h"
#include "xb-stack.h"

#define XB_TYPE_MACHINE (xb_machine_get_type ())
G_DECLARE_DERIVABLE_TYPE (XbMachine, xb_machine, XB, MACHINE, GObject)

struct _XbMachineClass {
	GObjectClass			 parent_class;
	/*< private >*/
	void (*_xb_reserved1)		(void);
	void (*_xb_reserved2)		(void);
	void (*_xb_reserved3)		(void);
	void (*_xb_reserved4)		(void);
	void (*_xb_reserved5)		(void);
	void (*_xb_reserved6)		(void);
	void (*_xb_reserved7)		(void);
};

/**
 * XbMachineDebugFlags:
 * @XB_MACHINE_DEBUG_FLAG_NONE:			No debug flags to use
 * @XB_MACHINE_DEBUG_FLAG_SHOW_STACK:		Show the stack addition and removal
 * @XB_MACHINE_DEBUG_FLAG_SHOW_PARSING:		Show the XPath predicate parsing
 *
 * The flags to control the amount of debugging is generated.
 **/
typedef enum {
	XB_MACHINE_DEBUG_FLAG_NONE		= 0,
	XB_MACHINE_DEBUG_FLAG_SHOW_STACK	= 1 << 0,
	XB_MACHINE_DEBUG_FLAG_SHOW_PARSING	= 1 << 1,
	/*< private >*/
	XB_MACHINE_DEBUG_FLAG_LAST
} XbMachineDebugFlags;

typedef gboolean (*XbMachineOpcodeFixupFunc)	(XbMachine		*self,
						 XbStack		*opcodes,
						 gpointer		 user_data,
						 GError			**error);
typedef gboolean (*XbMachineTextHandlerFunc)	(XbMachine		*self,
						 XbStack		*opcodes,
						 const gchar		*text,
						 gboolean		*handled,
						 gpointer		 user_data,
						 GError			**error);
typedef gboolean (*XbMachineMethodFunc)		(XbMachine		*self,
						 XbStack		*stack,
						 gboolean		*result,
						 gpointer		 exec_data,
						 gpointer		 user_data,
						 GError			**error);

XbMachine	*xb_machine_new			(void);
void		 xb_machine_set_debug_flags	(XbMachine		*self,
						 XbMachineDebugFlags	 flags);
XbStack		*xb_machine_parse		(XbMachine		*self,
						 const gchar		*text,
						 gssize			 text_len,
						 GError			**error);
gboolean	 xb_machine_run			(XbMachine		*self,
						 XbStack		*opcodes,
						 gboolean		*result,
						 gpointer		 exec_data,
						 GError			**error);

void		 xb_machine_add_opcode_fixup	(XbMachine		*self,
						 const gchar		*opcodes_sig,
						 XbMachineOpcodeFixupFunc fixup_cb,
						 gpointer		 user_data,
						 GDestroyNotify		 user_data_free);
void		 xb_machine_add_text_handler	(XbMachine		*self,
						 XbMachineTextHandlerFunc handler_cb,
						 gpointer		 user_data,
						 GDestroyNotify		 user_data_free);
void		 xb_machine_add_method		(XbMachine		*self,
						 const gchar		*name,
						 guint			 n_opcodes,
						 XbMachineMethodFunc	 method_cb,
						 gpointer		 user_data,
						 GDestroyNotify		 user_data_free);
void		 xb_machine_add_operator	(XbMachine		*self,
						 const gchar		*str,
						 const gchar		*name);

XbOpcode	*xb_machine_opcode_func_new	(XbMachine		*self,
						 const gchar		*func_name);
gchar		*xb_machine_opcode_to_string	(XbMachine		*self,
						 XbOpcode		*opcode)
G_DEPRECATED_FOR(xb_opcode_to_string);
gchar		*xb_machine_opcodes_to_string	(XbMachine		*self,
						 XbStack		*opcodes)
G_DEPRECATED_FOR(xb_stack_to_string);

XbOpcode	*xb_machine_stack_pop		(XbMachine		*self,
						 XbStack		*stack);
void		 xb_machine_stack_push		(XbMachine		*self,
						 XbStack		*stack,
						 XbOpcode		*opcode);
void		 xb_machine_stack_push_steal	(XbMachine		*self,
						 XbStack		*stack,
						 XbOpcode		*opcode);
void		 xb_machine_stack_push_text	(XbMachine		*self,
						 XbStack		*stack,
						 const gchar		*str);
void		 xb_machine_stack_push_text_static (XbMachine		*self,
						 XbStack		*stack,
						 const gchar		*str);
void		 xb_machine_stack_push_text_steal (XbMachine		*self,
						 XbStack		*stack,
						 gchar			*str);
void		 xb_machine_stack_push_integer	(XbMachine		*self,
						 XbStack		*stack,
						 guint32		 val);
void		 xb_machine_set_stack_size	(XbMachine		*self,
						 guint			 stack_size);
guint		 xb_machine_get_stack_size	(XbMachine		*self);

G_END_DECLS

#endif /* __XB_MACHINE_H */
