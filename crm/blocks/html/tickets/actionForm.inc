<?php
/**
 * @copyright 2011-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Ticket $this->ticket
 */
use Application\Models\Department;

$department = $_SESSION['USER']->getDepartment_id()
	? $_SESSION['USER']->getDepartment()
	: new Department();

$actions = $department->getActions();
$c       = count($actions);
if ($c) {
?>
<div class="actionForm">
	<h2><?= $this->_(['action', 'actions', $c]); ?></h2>
	<p><?= $this->_('add_action', 'messages'); ?></p>
	<form method="post" action="<?= BASE_URL; ?>/tickets/recordAction">
		<fieldset>
			<input name="ticket_id" type="hidden" value="<?= $this->ticket->getId(); ?>" />
			<table>
				<tr><td><label for="action_id" class="required">
							<?= $this->_('action'); ?>
							<span class="fa fa-asterisk"></span>
						</label>
					</td>
					<td><select name="action_id" id="action_id">
							<option></option>
							<?php
								foreach ($actions as $action) {
									$name = self::escape($action->getName());
									echo "<option value=\"{$action->getId()}\">$name</option>";
								}
							?>
						</select>
					</td>
				</tr>
				<tr><td><label for="actionDate"><?= $this->_('date'); ?></label>
						<p class="help">
							<?php
								// Create a human-readable version of the DATE_FORMAT
								// So that users know how to enter a date
								echo str_replace(array('Y','m','d'), array('yyyy','mm','dd'), DATE_FORMAT);
							?>
						</p>
					</td>
					<td><input name="actionDate" id="actionDate" value="<?= date(DATE_FORMAT); ?>" /></td>
				</tr>
			</table>
		</fieldset>
		<fieldset>
			<div><label for="notes"><?= $this->_(['comment', 'comments', 2]); ?></label></div>
			<div><textarea name="notes" id="notes"></textarea></div>
		</fieldset>
		<fieldset class="buttons">
			<button type="submit"><span class="fa fa-check"></span> <?= $this->_('submit'); ?></button>
			<button type="reset" ><span class="fa fa-times"></span> <?= $this->_('cancel'); ?></button>
		</fieldset>
	</form>
</div>
<?php
}
