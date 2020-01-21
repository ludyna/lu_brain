# lu_brain

[
	{ "keys": ["ctrl+t"], "command": "" },
	{ "keys": ["ctrl+shift+t"], "command": "" },
	{ "keys": ["ctrl+shift+s"], "command": "save_all" },
	{ "keys": ["ctrl+enter"], "command": "replace_all", "args": {"close_panel": true},
		 "context": [{"key": "panel", "operand": "replace"}, {"key": "panel_has_focus"}]
	},
	{ "keys": ["ctrl+left"], "command": "jump_back" },
	{ "keys": ["ctrl+right"], "command": "jump_forward" },
	{ "keys": ["ctrl+up"], "command": "next_view_in_stack" },
	{ "keys": ["ctrl+down"], "command": "prev_view_in_stack" },
	{ "keys": ["ctrl+n"], "command": "show_overlay", "args": {"overlay": "goto", "show_files": true} },
]