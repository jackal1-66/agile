      subroutine openlhef(filename)
      character *(*) filename
      OPEN(UNIT=97, FILE=filename)
      return
      end
