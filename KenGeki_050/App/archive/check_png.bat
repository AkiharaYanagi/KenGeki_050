@echo off
setlocal enabledelayedexpansion

REM チェック対象のルートディレクトリ（カレントディレクトリ）
set "root_dir=."

REM エラーログファイル
set "error_log=pngcrush_errors_recursive.txt"
echo PNG Crush Error Log (Recursive) > "%error_log%"

REM 一時ファイル（出力先）
set "temp_output=__temp_output.png"

REM 再帰的にPNGファイルを列挙
for /R "%root_dir%" %%F in (*.png) do (
    REM pngcrushを実行してエラー出力を一時ファイルに保存
    pngcrush -n -q "%%F" "%temp_output%" 2> temp_error.txt

    REM エラーが出ていたらログに記録
    findstr /i /c:"error" temp_error.txt >nul
    if !errorlevel! EQU 0 (
        echo %%F にエラーあり >> "%error_log%"
    )

    REM 一時エラーファイルを削除
    del temp_error.txt >nul 2>&1
)

REM 一時出力ファイルを削除
del "%temp_output%" >nul 2>&1

echo 再帰チェック完了。エラーのあるファイルは "%error_log%" に記録されています。
pause
