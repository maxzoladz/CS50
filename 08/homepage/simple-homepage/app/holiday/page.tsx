import React from "react";
import { Input } from "@nextui-org/react";

export default function Page() {
  return (
    <div className="h-screen w-screen flex justify-center items-center">
      <div className="flex w-auto gap-4">
        <Input type="email" label="Email" placeholder="Enter your email" />
        <Input type="email" label="Email" placeholder="Enter your email" />
      </div>
    </div>
  );
}
