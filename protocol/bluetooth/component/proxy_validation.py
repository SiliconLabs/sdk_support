# Proxy validation script

def validate(project):
  proxy_server_present = project.is_selected('btmesh_feature_proxy_client')
  proxy_client_present = project.is_selected('btmesh_feature_proxy_server')
  proxy_present = project.is_selected('btmesh_feature_proxy')

  if proxy_present and not (proxy_server_present or proxy_client_present) :
      project.warning(
                'If you add proxy component then either proxy server or proxy client will also be needed',
                 project.target_for_project(),
                 'Add either proxy_server or proxy_client component)'
            )
