<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Ticket $this->ticket
 */
use Blossom\Classes\View;

$c = $this->ticket->getCategory();
$service_name = $c ? self::escape($c->getName()) : '';
$service_code = $c ? $c->getId() : '';

$status = strtolower($this->ticket->getStatus());

$issue = $this->ticket->getIssue();
$description = self::escape($issue->getDescription());

$h = $this->ticket->getHistory();
$history = end($h);

$address = self::escape($this->ticket->getLocation());
$zipcode = self::escape($this->ticket->getZip());

$media_url = '';
$media = $issue->getMedia();
if (count($media)) {
	$m = $media->current();
	$media_url = $m->getURL();
}

$agency_responsible = '';
$p = $this->ticket->getAssignedPerson();
if ($p) {
	$d = $p->getDepartment();
	if ($d) {
		$agency_responsible = self::escape($d->getName());
	}
}

echo "
<service_requests>
	<request>
		<service_request_id>{$this->ticket->getId()}</service_request_id>
		<status>$status</status>
		<service_name>$service_name</service_name>
		<service_code>$service_code</service_code>
		<description>$description</description>
		<agency_responsible>$agency_responsible</agency_responsible>
		<requested_datetime>{$this->ticket->getEnteredDate('c')}</requested_datetime>
		<updated_datetime>{$history->getEnteredDate('c')}</updated_datetime>
		<address>$address</address>
		<address_id>{$this->ticket->getAddressId()}</address_id>
		<zipcode>$zipcode</zipcode>
		<lat>{$this->ticket->getLatitude()}</lat>
		<long>{$this->ticket->getLongitude()}</long>
		<media_url>$media_url</media_url>
	</request>
</service_requests>
";
