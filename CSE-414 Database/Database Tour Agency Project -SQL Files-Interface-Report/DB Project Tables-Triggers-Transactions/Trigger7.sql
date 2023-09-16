DELIMITER //

CREATE TRIGGER decreaseSeatingCapacity
AFTER INSERT ON booking
FOR EACH ROW
BEGIN
    IF (SELECT seatingCapacity FROM bus WHERE busID = NEW.busID) = 0 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Cannot insert tour. Bus seating capacity is already 0.';
    ELSE    
		UPDATE bus SET seatingCapacity = seatingCapacity - 1 WHERE busID = NEW.busID;
    END IF;    
END//

DELIMITER ;
