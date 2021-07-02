def validate(project):
  if project.is_provided('bluetooth_feature_advertiser') == False and project.is_provided('bluetooth_feature_scanner') == False:
    project.warning("Bluetooth connection requires Either scanning or advertising capability",project.target_for_project())

