<?php
$memcache = new \Memcache;
$memcache->connect('localhost', 11211) or die ("Connexion impossible");

$version = $memcache->getVersion();
echo "Version du serveur : ".$version."<br/>\n";

$tmp_object = new stdClass;
$tmp_object->str_attr = 'test';
$tmp_object->int_attr = 123;

$memcache->set('key', $tmp_object, false, 10) or die ("Echec de la sauvegarde des donn�es sur le serveur");
echo "Les donn�es ont �t� stock�es dans le cache (les donn�es expireront dans 10 secondes)<br/>\n";

$get_result = $memcache->get('key');
echo "Donn�es depuis le cache :<br/>\n";

var_dump($get_result);
