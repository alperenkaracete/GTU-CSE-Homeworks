DELIMITER //

CREATE TRIGGER insertBookingUpdateRooms
AFTER INSERT ON booking
FOR EACH ROW
BEGIN
    IF NEW.hotelID IS NOT NULL THEN
        UPDATE hotel SET roomCount = roomCount - 1 WHERE hotelID = NEW.hotelID;
    END IF;
END//

DELIMITER ;