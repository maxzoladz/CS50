import React from "react";
import ContactForm from "@/components/ContactForm";

export default function Page() {
  return (
    <div className="w-screen h-screen bg-cover bg-center flex items-center justify-center">
      <div className="h-80 w-96 relative bg-cover bg-center bg-neutral-700 rounded-xl border border-neutral-900">
        <div className="flex mt-8 justify-center left-20 bottom-16 w-auto md:w-auto">
          <ContactForm />
        </div>
      </div>
    </div>
  );
}
