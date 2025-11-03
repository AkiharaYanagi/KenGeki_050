Get-ChildItem *.png | ForEach-Object {
    $output = & pngcheck -v $_.FullName
    if ($output -match "iCCP") {
        Write-Output "$($_.Name) は未処理の可能性があります"
    }
}
