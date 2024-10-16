$arduinoLibrariesPath = "$env:USERPROFILE\Documents\Arduino\libraries"

$libraries = @(
	"https://github.com/lexus2k/ssd1306.git"
	"https://github.com/ElectronicCats/mpu6050.git"
	"https://github.com/matmunk/DS18B20.git"
	"https://github.com/NorthernWidget/DS3231.git"
)

if (-Not (Test-Path $arduinoLibrariesPath)) {
	New-Item -Path $arduinoLibrariesPath -ItemType Directory
}

function Clone-Library($url) {
	$repoName = [IO.Path]::GetFileNameWithoutExtension($url)
	$destinationPath = "$arduinoLibrariesPath\$repoName"

	if (-Not (Test-Path $destinationPath)) {
		git clone $url $destinationPath
		Write-Host "$repoName cloned successfully."
	} else {
		Write-Host "$repoName already exists. Skipping."
	}
}

foreach ($library in $libraries) {
	Clone-Library $library
}

Write-Host "Libraries cloned successfully!"