<?php

// This is the code of the php code...
// Due we have already compiled and installed the ROOTKIT module
// we might see here how works.

// First of all we will call the first native hooked method: 'hash()'
printf('<p>Requesting new hash()...</p>');
printf('<p>%s</p>', hash('sha256', rand()));

// Then we will call the other one native function hooked: 'md5()'
printf('<p>Requesting new md5()...</p>');
printf('<p>%s</p>', md5(rand()));