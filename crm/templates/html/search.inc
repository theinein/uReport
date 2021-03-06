<!DOCTYPE html>
<html lang="<?= strtolower(substr(LOCALE,0,2)); ?>">
<?php
	$this->layout = 'twoColumn_300-a';
	$dir = dirname(__FILE__);
	include $dir.'/partials/header.inc';
?>
<body>
	<?php
		include $dir.'/partials/banner.inc';
		include $dir.'/partials/menubar.inc';

		$this->addToAsset('scripts', JQUERY.'/jquery.min.js');
		$this->addToAsset('scripts', BASE_URI.'/js/slidingPanel.js');
	?>
	<div id="panel-container">
		<div id="left" class="panel">
			<?= $this->includeBlocks('left'); ?>
		</div>
		<div id="right" class="panel">
			<?php
				include BLOSSOM.'/errorMessages.php';
				echo $this->includeBlocks('right');
			?>
		</div>
	</div>
	<?php include $dir.'/partials/footer.inc'; ?>
</body>
</html>
<?php
	include $dir.'/partials/garbageCollection.inc';
?>
