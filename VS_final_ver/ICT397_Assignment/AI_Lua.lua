function DefaultExecuteUpdate()
	distance = 50.0
	new_state = "flee_state"
	return distance, new_state
end

function FleeExecuteUpdate()
	distance = 50.0
	new_state = "Default_state"
	return distance, new_state
end