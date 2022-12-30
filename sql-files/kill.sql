
CREATE TABLE `killlog` (
  `kill_id` mediumint(9) unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime NOT NULL,
  `char_id` int(11) NOT NULL DEFAULT 0,
  `type` enum('C','M','N','S') NOT NULL DEFAULT 'S',
  `class_id` int(11) NOT NULL DEFAULT 0,
  `monster_id` int(11) NOT NULL DEFAULT 0,
  `map` varchar(11) NOT NULL DEFAULT '',
  PRIMARY KEY (`kill_id`),
  KEY `char_id` (`char_id`),
  KEY `class_id` (`class_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
