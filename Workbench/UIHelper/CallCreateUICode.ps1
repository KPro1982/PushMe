#Output File Name Definitions
Param($layoutname, $layoutpath)


$TempFile = 'Temp.txt'
$definitionsFile = 'Definitions.txt'
$castsFile = 'Casts.txt'
$switchFile = 'Switch.txt'
$Pattern = 'Class'
$columnwhitespace = 35

$SourceFile = $layoutpath 


# Remove next 2 lines if you generally prefer to keep PanelWidgets
Write-Host A `'y`' answer to the following question will excluded all PanelWidgets from the output.
Write-Host `'Enter`' includes PanelWidgets
Write-Host
$ExcludePanel = Read-Host Exclude Panel Widgets?



$ExcludeTerm = "~"



# Remove existing temp file

If (Test-Path -Path $TempFile ) {
Remove-Item $TempFile
}

If (Test-Path -Path $definitionsFile ) {
Remove-Item $definitionsFile
}

If (Test-Path -Path $castsFile ) {
Remove-Item $castsFile
}

If (Test-Path -Path $switchFile ) {
Remove-Item $switchFile
}


# Create temp file 
New-Item $TempFile | Out-Null

# Formatting temp file to exclude unnecessary lines and chars
(Get-Content $SourceFile) | Where-Object { $_ -match $Pattern } | Set-Content $TempFile


(Get-Content $TempFile).Trim() -ne '' | Set-Content $TempFile


((Get-Content -path $TempFile -Raw) -replace '{','') | Set-Content -Path $TempFile


((Get-Content -path $TempFile -Raw) -replace 'Class','') | Set-Content -Path $TempFile

((Get-Content -path $TempFile -Raw) -replace 'FrameWidget','Widget') | Set-Content -Path $TempFile

#Remove excluded widgets from temp file
$lines = Get-Content -Path $TempFile
if($ExcludePanel -eq 'y')
{
	$lines = $lines | Where-Object { -not $_.Contains('Panel') }
}
if($ExcludeTerm -ne '')
{
	$lines = $lines | Where-Object { -not $_.Contains($ExcludeTerm) }
}

# remove empty lines from array
$lines = $lines | Where-Object {$_}

# Create definitions file 
New-Item $definitionsFile | Out-Null
$Tab = [char]9

# Existing $lines array is used as temp file contains excluded widgets
foreach ($line in $lines) {
	$buffer = ""

	if ($line.length -gt 1)
	{
		$strArr = $line.Split(" ") 
		$strArr[0] = "private " + $strArr[0]
		$strArr[1] = " " + "m_" + $strArr[1] + ";"

		
		# justify text
		$deflen = $strArr[0].Length
		$bufferlen = $columnwhitespace - $deflen
		for($i = 0; $i -lt $bufferlen; $i++)
		{
			$buffer += ' '	
			
		}
				
		$definition =  $strArr[0] + $buffer + $strArr[1]		
		$definition | Out-File -append $definitionsFile
	}
 }
 

 
# Create casts file

 
 New-Item $castsFile | Out-Null
 
$Tab = [char]9
$nl = [char]13
$eq = "="
$quote = '"'
$cast = ".Cast(layoutroot.FindAnyWidget("
$close = "));"

# Existing $lines array is used as temp file contains excluded widgets
foreach ($line in $lines) {
	$buffer = ""
	$strArr = $line.Split(" ") 
    $strVar = "m_" + $strArr[1]
	
	
	# justify text
	$deflen = $strVar.Length
	$bufferlen = $columnwhitespace - $deflen
	for($i = 0; $i -lt $bufferlen; $i++)
	{
		$buffer += ' '	
		
	}
	
	$firstpart = $strVar + $buffer	
	
	$castline =  $firstpart + " $eq   " + $strArr[0] + $cast + $quote + $strArr[1] + $quote + $close
	$castline | Out-File -append $castsFile
 }
 
 # Write Switch File 

 
 "switch(w)" | Out-File -append $switchFile
 "{" | Out-File -append $switchFile
 
 foreach ($line in $lines) {

	$strArr = $line.Split(" ") 
    $strVar = "m_" + $strArr[1]
	
	# case m_buttonname
	$Tab + "case " + "$strVar" + ":" | Out-File -append $switchFile
	$nl + $Tab + $Tab + "`/`/  Your code goes here" + $nl | Out-File -append $switchFile
	# break
	$nl + $Tab + "break;" | Out-File -append $switchFile
	$nl | Out-File -append $switchFile
	
	
 }
 
"}" | Out-File -append $switchFile


