<?php
/**
 * Where on the filesystem this application is installed
 */
define('APPLICATION_HOME', __DIR__);
define('BLOSSOM', APPLICATION_HOME.'/vendor/City-of-Bloomington/blossom-lib');

/**
 * Multi-Site support
 *
 * To allow multiple sites to use this same install base,
 * define the SITE_HOME variable in the Apache config for each
 * site you want to host.
 *
 * SITE_HOME is the directory where all site-specific data and
 * configuration are stored.  For backup purposes, backing up this
 * directory would be sufficient for an easy full restore.
 */
define('SITE_HOME', !empty($_SERVER['SITE_HOME']) ? $_SERVER['SITE_HOME'] : __DIR__.'/data');
include SITE_HOME.'/site_config.inc';

/**
 * Enable autoloading for the PHP libraries
 */
require_once APPLICATION_HOME.'/vendor/zendframework/zend-loader/src/AutoloaderFactory.php';
$config = [
	'Zend\Loader\StandardAutoloader' => [
		'namespaces' => [
			'Application' => APPLICATION_HOME,
			'Site'        => SITE_HOME,
            'Blossom'     => BLOSSOM.'/src',
            'Interop\Container'    => APPLICATION_HOME.'/vendor/container-interop/container-interop/src/Interop/Container',
            'Zend\Stdlib'          => APPLICATION_HOME.'/vendor/zendframework/zend-stdlib/src',
            'Zend\Permissions\Acl' => APPLICATION_HOME.'/vendor/zendframework/zend-permissions-acl/src',
            'Zend\Paginator'       => APPLICATION_HOME.'/vendor/zendframework/zend-paginator/src',
            'Zend\Log'             => APPLICATION_HOME.'/vendor/zendframework/zend-log/src',
            'Zend\Loader'          => APPLICATION_HOME.'/vendor/zendframework/zend-loader/src',
            'Zend\Db'              => APPLICATION_HOME.'/vendor/zendframework/zend-db/src',
            'Zend\ServiceManager'  => APPLICATION_HOME.'/vendor/zendframework/zend-servicemanager/src'
		],
		'prefixes' => [
			'Apache'               => APPLICATION_HOME.'/vendor/reprovinci/solr-php-client/Apache'
		]
	]
];
Zend\Loader\AutoloaderFactory::factory($config);

include APPLICATION_HOME.'/access_control.inc';

/**
 * Session Startup
 * Don't start a session for CLI usage.
 * We only want sessions when PHP code is executed from the webserver
 */
if (!defined('STDIN')) {
	ini_set('session.save_path', SITE_HOME.'/sessions');
	ini_set('session.cookie_path', BASE_URI);
	session_start();
}

/**
 * Skidder is a web service for error loggin.  This application supports
 * logging errors to a Skidder server.  You must register for an application_id
 * on the skidder server you want to post errors to.
 */
//$writer = new Blossom\Classes\Log\SkidderWriter('http://localhost/skidder/index', 100 );
//$logger = new Zend\Log\Logger();
//$logger->addWriter($writer);
//Zend\Log\Logger::registerErrorHandler($logger);
//Zend\Log\Logger::registerExceptionHandler($logger);
//Zend\Log\Logger::registerFatalErrorShutdownFunction($logger);

/**
 * PHP command line executable
 *
 * Needed to run background workers
 */
define('PHP', '/usr/local/bin/php');

/**
 * Image handling library
 * Set the path to the ImageMagick binaries
 */
define('IMAGEMAGICK','/usr/bin');

/**
 * Grab a timestamp for calculating process time
 */
$startTime = microtime(1);