((nil . ((eval . ( progn
                   (setq dap-print-io t)
   ;(setq dap-ui-buffer-configurations nil)
   ;(setq dap-auto-configure-features '(sessions controls tooltip breakpoints))

   (require 'dap-gdb)
   (setq dap-auto-configure-features nil)
   (setq dap-gdb-gdb-path "xtensa-esp32-elf-gdb")
   (setq dap-gdb-debug-program '("xtensa-esp32-elf-gdb" "-i" "dap"))
   (dap-register-debug-template "ESP32 OpenOCD"
    (list 
      :name "ESP32 OpenOCD"
      :type "gdbserver"
      :request "attach"

      ;; Your ELF file
      :program "${workspaceFolder}/build/niceview.elf"
      :target "localhost:3333"
      :gdbpath "xtensa-esp32-elf-gdb"

      ;; OpenOCD GDB server

      ;; Optional: point Emacs to source dirs so it resolves breakpoints
      :cwd "${workspaceFolder}"
      :stopAtEntry :json-false
      :initCommands
      (list
       "echo >>> INITCOMMANDS RAN <<<"
       ;"source ${workspaceFolder}/build/gdbinit/connect"
       "source ${workspaceFolder}/build/gdbinit/prefix_map"
       "source ${workspaceFolder}/build/gdbinit/symbols"
       )
      )
   ))))))
