//  Copyright (c) 2007-2010 Facebook
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
// See accompanying file LICENSE or visit the Scribe site at:
// http://developers.facebook.com/scribe/
//
// @author Johan Stille
// @author Björn Sperber
// @author Wouter de Bie

#include "file_path_policy_factory.h"
#include "dynamic_file_path_policy.h"
#include "static_file_path_policy.h"
#include "timestamped_file_path_policy.h"
#include "common.h"
#include "env_default.h"

boost::shared_ptr<FilePathPolicy> FilePathPolicyFactory::createFilePathPolicy(const std::string & filePath,
                                                                              const std::string & subDirectory,
                                                                              bool isConfiguredToRoll) {
  if (filePathIsDynamicallyConfigured(filePath)) {
    if (!subDirectory.empty()) {
      LOG_OPER("Path is dynamically configured. sub_directory and use_hostname_sub_directory will be ignored.");
    }
    return boost::shared_ptr<FilePathPolicy>(new DynamicFilePathPolicy(filePath));
  } else if (isConfiguredToRoll) {
    return boost::shared_ptr<FilePathPolicy>(new TimestampedFilePathPolicy(filePath, subDirectory));
  } else {
    return boost::shared_ptr<FilePathPolicy>(new StaticFilePathPolicy(filePath, subDirectory));
  }
}

bool FilePathPolicyFactory::filePathIsDynamicallyConfigured(const std::string & filePath) {
  return filePath.find("\%") != std::string::npos;
}
