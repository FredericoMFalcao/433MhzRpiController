<?php
/*
*	1. List all available signals
*/
$availableSignals = [];
foreach(scandir(__DIR__) as $file) 
	if (substr($file, -4) == ".bin")
		$availableSignals[$file] = basename($file);

/*
*	2. Transmit signal
*/
if (isset($_GET) && isset($_GET['action']) && $_GET['action'] == "send") {
	exec("sudo ".__DIR__."/sendSignal {$_GET['name']} 2>&1", $output, $retVal);
	if ($retVal > 0)
		$message = implode("\n", $output);
	else
		$message = "successfully transmited signal";
}
/*
*	3. Record signal
*/
if (isset($_GET) && isset($_GET['action']) && $_GET['action'] == "record") {
	exec("sudo ".__DIR__."/recordSignal {$_GET['name']}.bin", $output, $retVal);
	if ($retVal > 0)
		$message = implode("\n", $output);
	else
		$message = "successfully recorded signal";

}
/*
*	4. Delete signal
*/
if (isset($_GET) && isset($_GET['action']) && $_GET['action'] == "delete") {
	exec("sudo rm ".__DIR__."/".$_GET['name'], $output, $retVal);
	if ($retVal > 0)
		$message = implode("\n", $output);
	else
		$message = "signal deleted";

}



?>
<html>
<head>
	<title>Gates Remote Controller</title>
</head>
<body>
<?php if (isset($message) && !empty($message)) : ?>
<pre><?=$message?></pre>
<hr>
<?php endif; ?>
<h1>Record new signal</h1>
<form method="GET">
	Name:<input name="name" value="" />
	<input type="submit" name="action" value="record" />
</form>
<hr>
<h1>All available signals</h1>
<table>
<thead>
	<tr>
		<th>Name</th>
		<th>&nbsp;</th>
		<th>&nbsp;</th>
	</tr>
</thead>
<tbody>
<?php foreach($availableSignals as $signal) : ?>
<tr>
<td><?=$signal?></td>
<td><a href="?action=send&name=<?=urlencode($signal)?>">Transmit</a></td>
<td><a href="?action=delete&name=<?=urlencode($signal)?>">Delete</a></td>
</tr>
<?php endforeach; ?>
</tbody>
</table>
</body>
</html>
