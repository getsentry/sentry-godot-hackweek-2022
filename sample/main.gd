extends Node

func _ready() -> void:
	SentrySdk.setDsn("https://3f1e095cf2e14598a0bd5b4ff324f712@o447951.ingest.sentry.io/6680910")
	SentrySdk.setDebug(true)
	SentrySdk.init()
	
	SentrySdk.addBreadcrumb("My Type", "Some breadcrumb")
	SentrySdk.captureEvent("My very own godot event!")
	SentrySdk.captureError("Happy Godot error!")
