DELIMITER //

CREATE TRIGGER deleteBookingUpdateRooms
AFTER DELETE ON booking
FOR EACH ROW
BEGIN
    IF OLD.hotelID IS NOT NULL THEN
        UPDATE hotel SET roomCount = roomCount + 1 WHERE hotelID = OLD.hotelID;
    END IF;
END//

DELIMITER ;