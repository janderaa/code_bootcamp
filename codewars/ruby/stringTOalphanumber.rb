def alphabet_position(text)
  # time = 29.2606ms
  # Completion = 2 hours
  output = ""
  text.split('').each { |letter|
    if letter.match?(/[A-Za-z]/)
      temp = letter.downcase.bytes[0]
      if temp >= 97 && temp <=122
        output += "#{temp-96} "
      end
    end
  }
  output.chop
end