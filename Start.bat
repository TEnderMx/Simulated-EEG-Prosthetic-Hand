set PROJ_DIR="C:\Users\mosta\Desktop\Ender\College\ZE FINAL PROJECT"

wt -d %PROJ_DIR% cmd /k "title Camera & venv\Scripts\activate & python Software\mediapipe_lsl.py" ; split-pane -p "Command Prompt" -d %PROJ_DIR% cmd /k "title Encoder & venv\Scripts\activate & encoder"