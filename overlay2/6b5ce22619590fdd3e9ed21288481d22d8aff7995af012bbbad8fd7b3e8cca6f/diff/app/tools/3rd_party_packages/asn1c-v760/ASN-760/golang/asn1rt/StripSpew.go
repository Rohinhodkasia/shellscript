// StripSpew accepts a string of output from spew and returns a string that
// has <nil> pointers and most type information stripped out.
func StripSpew(spewOutput string) string {
	var sb strings.Builder
	var matchFound bool = false
	var newpiece string

	// Compile regular expression to detect nil pointers.
	renil, _ := regexp.Compile(`<nil>`)

	// Compile a regular expression to detect type information.
	retype, _ := regexp.Compile(`(^.*?\:\s+)\(.*?\)`)

	pieces := strings.Split(spewOutput, "\n")
	for _, piece := range pieces {
		if len(piece) == 0 {
			sb.WriteByte('\n')
			continue
		}

		// See if a nil pointer is indicated.  If so, we remove this item from
		// the output.
		if renil.MatchString(piece) {
			matchFound = true
			continue
		} else {
			newpiece = piece
		}

		// See if type information is indicated.  If so, we remove it.
		if retype.MatchString(piece) {
			matchFound = true
			newpiece = retype.ReplaceAllString(piece, "$1")
		}
		sb.WriteString(newpiece)
		sb.WriteByte('\n')
	}
	if matchFound {
		return sb.String()
	}

	return spewOutput
}
