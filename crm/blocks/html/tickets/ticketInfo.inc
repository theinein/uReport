<?php
/**
 * @copyright 2011-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Ticket $this->ticket
 * @param bool $this->disableButtons
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;

use Blossom\Classes\Url;

$ticket_id = $this->ticket->getId();
$location  = self::escape($this->ticket->getLocation());
$location  = $location
	? "<a href=\"".BASE_URL."/locations/view?location=".urlencode($location)."\">$location</a>"
	: '';

$userCanViewPeople = Person::isAllowed('people', 'view');
$url = new Url(BASE_URL.'/people/view.php');

$personFields = ['enteredBy', 'assigned'];
foreach ($personFields as $field) {
    $$field = '';
    $get = 'get'.ucfirst($field).'Person';
    $person = $this->ticket->$get();
    if ($person) {
        $$field = self::escape($person->getFullname());
        if ($userCanViewPeople) {
            $url->person_id = $person->getId();
            $$field = "<a href=\"$url\">{$$field}</a>";
        }
    }
}

$status = $this->ticket->getStatus();
if ($this->ticket->getSubstatus()) {
	$status.= ': '.$this->ticket->getSubstatus();
}

$editStatusButton     = '';
$deleteButton         = '';
$changeCategoryButton = '';
$changeLocationButton = '';
$assignButton         = '';

if (!$this->disableButtons) {
	$helper = $this->template->getHelper('buttonLink');

	if (Person::isAllowed('tickets', 'changeStatus')) {
        $editStatusButton = $helper->buttonLink(
            BASE_URI.'/tickets/changeStatus?ticket_id='.$ticket_id,
            $this->_('change_status'),
            'edit',
            ButtonLink::SIZE_ICON,
            ['data-callback'=>'changeStatus']
        );
    }
	if (Person::isAllowed('tickets', 'delete')) {
		$deleteButton = $helper->buttonLink(
			BASE_URI.'/tickets/delete?ticket_id='.$ticket_id,
			$this->_('delete_ticket'),
			'delete'
		);
	}

	if ($this->ticket->getStatus()!='closed') {
        if (Person::isAllowed('tickets', 'changeCategory')) {
            $changeCategoryButton = $helper->buttonLink(
                BASE_URI.'/tickets/changeCategory?ticket_id='.$ticket_id,
                $this->_('change_category'),
                'edit',
                ButtonLink::SIZE_ICON,
                ['data-callback'=>'changeCategory']
            );
        }
        if (Person::isAllowed('tickets', 'changeLocation')) {
            $changeLocationButton = $helper->buttonLink(
                BASE_URI.'/tickets/changeLocation?ticket_id='.$ticket_id,
                $this->_('change_location'),
                'edit',
                ButtonLink::SIZE_ICON,
                ['data-callback'=>'changeLocation']
            );
        }
		if (Person::isAllowed('tickets', 'assign')) {
			$assignButton = $helper->buttonLink(
				BASE_URI.'/tickets/assign?ticket_id='.$ticket_id,
				$this->_('assign_ticket'),
				'edit',
				ButtonLink::SIZE_ICON,
				['data-callback'=>'assign']
			);
		}
	}

}

$category = $this->ticket->getCategory_id()
	? self::escape($this->ticket->getCategory()->getName())
	: '';
echo "
<div class=\"ticketInfo twoColumnlist\">
	<h2><a href=\"{$this->ticket->getURL()}\">Case #{$ticket_id}</a> $deleteButton</h2>
	<ul>
		<li><label>{$this->_('category_id')}:</label>
			$category
			$changeCategoryButton
		</li>
		<li><label>{$this->_('location')}:</label>
			$location
			$changeLocationButton
		</li>
		<li><label>{$this->_('status')}:</label>
			$status
			$editStatusButton
		</li>
		<li><label>{$this->_('assignedPerson_id')}:</label>
			$assigned
			$assignButton
		</li>
		<li><label>{$this->_('enteredByPerson_id')}:</label>
			$enteredBy
		</li>
	";
	$client = $this->ticket->getClient();
	if ($client) {
		$name = self::escape($client->getName());
		echo "
		<li>
			<label>Received Via:</label>
			$name
		</li>
		";
	}
echo "
		<li><label>Date Opened:</label>
			{$this->ticket->getEnteredDate(DATE_FORMAT)}
		</li>
		<li><label>Date Closed:</label>
			{$this->ticket->getClosedDate(DATE_FORMAT)}
		</li>
		<li><label>Last Modified:</label>
			{$this->ticket->getLastModified(DATE_FORMAT)}
		</li>
	</ul>
</div>
<script type=\"text/javascript\">
	CRM.ticket_id = {$this->ticket->getId()};
</script>
";
$this->template->addToAsset('scripts', JQUERY.'/jquery.min.js');
$this->template->addToAsset('scripts', BASE_URI.'/js/tickets/actionForms.js');
