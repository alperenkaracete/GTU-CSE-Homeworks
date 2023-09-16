INSERT INTO agent (tourID, agencyID, agentName, agentTelephone, salary,available) VALUES
(1, 1, 'Burak Aksu', '0532 777 77 77', 20000,false),
(2, 1, 'Sevda Hacıoğlu', '0531 222 22 22', 20000,false),
(3, 2, 'Duran Yılmaz', '0541 111 11 11', 20000,false),
(4, 2, 'Gökay Türe', '0554 333 33 33', 20000,false),
(NULL, 2, 'Berke Geçmen', '0554 666 66 66', 20000,true);

SELECT * FROM agent;